/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:27 by utilisateur       #+#    #+#             */
/*   Updated: 2024/06/05 13:26:42 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	management_fd(t_pipe *save_fd, int i)
{
	if (i == 0)
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	if (i == save_fd->nmb_max_cmd - 1)
	{
		dup2(save_fd->previous, STDIN_FILENO);
		dup2(save_fd->std_fd[1], STDOUT_FILENO);
		close(save_fd->previous);
	}
	else if (i > 0)
	{
		dup2(save_fd->previous, STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
		close(save_fd->previous);
	}
	else if (i == -1)
	{
		dup2(save_fd->std_fd[0], STDIN_FILENO);
		dup2(save_fd->std_fd[1], STDOUT_FILENO);
	}	// write(1, "coucou\n", 8);
}

int	ft_lst_command_size(t_command *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_lst_command_size(lst->next));
}

int	free_and_close(t_pipe *fds, t_command_line *line, t_int_list *pid, t_list **env)
{
	if(env && *env)
		ft_lstclear(env, free);
	if (line)
		free_struct(line);
	if (ft_int_lstsize(pid) < fds->nmb_max_cmd)
		fds->previous = dup(fds->pipe[0]);
	if (pid)
		ft_int_lstclear(&pid);
	close(fds->pipe[0]);
	close(fds->pipe[1]);
	dup2(fds->std_fd[0], STDIN_FILENO);
	dup2(fds->std_fd[1], STDOUT_FILENO);
	return (0);
}

int	main_pipe(t_command_line *cmd_line, t_list **envp)
{
	int			error;
	t_pipe		pipe_fds;
	t_command_line	*current;
	t_int_list		*forks;
	t_int_list		*new_elemt;
	t_int_list		*to_remove;

	forks = NULL;
	error = 0;
	pipe_fds.previous = 0;
	pipe_fds.std_fd[0] = dup(STDIN_FILENO);
	pipe_fds.std_fd[1] = dup(STDOUT_FILENO);
	pipe_fds.nmb_max_cmd = ft_lst_command_size(cmd_line->commands);
	current = cmd_line;
	if (pipe_fds.nmb_max_cmd == 1)
	{
		main_redirection(cmd_line, pipe_fds.std_fd, *envp);
		cmd_line->return_value = main_execution(current, *envp, &pipe_fds);
		close(pipe_fds.std_fd[0]);
		close(pipe_fds.std_fd[1]);
		return(cmd_line->return_value);
	}
	while (current->commands)
	{
		if (pipe(pipe_fds.pipe))
			return (free_and_close(&pipe_fds, cmd_line, forks, NULL));
		new_elemt = ft_int_lstnew(fork());
		if (!new_elemt)
			return (free_and_close(&pipe_fds, cmd_line, forks, NULL));
		if ((pid_t) (new_elemt->content) == 0)
		{
			// printf("pipe[0] -> %d\npipe[1] -> %d\nstd_fd[0] -> %d\nstd_fd[1] -> %d\n", pipe_fds.pipe[0], pipe_fds.pipe[1],  pipe_fds.std_fd[0], pipe_fds.std_fd[1]);
			management_fd(&pipe_fds, ft_int_lstsize(forks));
			main_redirection(cmd_line, pipe_fds.std_fd, *envp);
			if (!cmd_line->error_code)
				cmd_line->return_value = main_execution(current, *envp, &pipe_fds);
			else
				cmd_line->return_value = cmd_line->error_code;
			free_and_close(&pipe_fds, cmd_line, NULL, NULL);
			
			
			close(pipe_fds.std_fd[0]);
			close(pipe_fds.std_fd[1]);
			close(pipe_fds.previous);
			exit(cmd_line->return_value);
		}
		else if ((pid_t)(new_elemt->content) > 0)
		{
			if (cmd_line->error_code)
			{
				error = cmd_line->error_code;
				cmd_line->error_code = 0;
			}
			ft_int_lstadd_back(&forks, new_elemt);
			if (pipe_fds.previous)
				close(pipe_fds.previous);
			free_and_close(&pipe_fds, NULL, NULL, NULL);
			current->commands = current->commands->next;
		}
	}
	new_elemt = forks;
	close(pipe_fds.std_fd[0]);
	close(pipe_fds.std_fd[1]);
	free_and_close(&pipe_fds, NULL, NULL, NULL);
	while (ft_int_lstsize(forks))
	{
		// printf("%d\n", ft_int_lstsize(forks));
		to_remove = NULL;
		forks->content = waitpid(((pid_t) forks->content), &error, 0);
		if ((pid_t)(forks->content) <= 0)
			to_remove = forks;
		if (!forks->next)
			forks = new_elemt;
		else
			forks = forks->next;
		if(to_remove)
			ft_int_lst_remove_index(&forks, ft_int_lst_get_index(forks, to_remove));
		cmd_line->return_value = WEXITSTATUS(error);
	}
	// printf("%d\n", WEXITSTATUS(error));
	return (error);
}

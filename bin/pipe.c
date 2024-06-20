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

int	ft_lst_command_size(t_command *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_lst_command_size(lst->next));
}

int	close_pipe(t_pipe *save_fd)
{
	if (save_fd->pipe1[0] != -1)
		close(save_fd->pipe1[0]);
	if (save_fd->pipe2[0] != -1)
		close(save_fd->pipe2[0]);
	if (save_fd->pipe1[1] != -1)
		close(save_fd->pipe1[1]);
	if (save_fd->pipe2[1] != -1)
		close(save_fd->pipe2[1]);
	return (0);
}

int	open_pipe(t_pipe *save_pipe)
{
	if (save_pipe->pipe1[0] == -1 && save_pipe->pipe2[0] == -1)
	{
		if (pipe(save_pipe->pipe1))
			return (-1);
		if (pipe(save_pipe->pipe2))
			return (-1);
	}
	return (0);
}

void	first_cmd(t_pipe *save_fd)
{
	if (save_fd->redirs != 2 && save_fd->redirs != 3)
		dup2(save_fd->std_fd[0], STDIN_FILENO);
	if (save_fd->redirs != 1 && save_fd->redirs != 3
		&& save_fd->nmb_max_cmd > 1)
	{
		dup2(save_fd->pipe1[1], STDOUT_FILENO);
		close(save_fd->pipe1[1]);
		save_fd->pipe1[1] = -1;
	}
}

void	other_cmd(t_pipe *save_fd)
{
	if (save_fd->redirs != 2 && save_fd->redirs != 3)
	{
		dup2(save_fd->pipe1[0], STDIN_FILENO);
		close(save_fd->pipe1[0]);
		save_fd->pipe1[0] = -1;
	}
	if (save_fd->redirs != 1 && save_fd->redirs != 3)
	{
		dup2(save_fd->pipe2[1], STDOUT_FILENO);
		close(save_fd->pipe2[1]);
		save_fd->pipe1[1] = -1;
	}
}

void	other_cmd_pair(t_pipe *save_fd)
{
	if (save_fd->redirs != 2 && save_fd->redirs != 3)
	{
		dup2(save_fd->pipe2[0], STDIN_FILENO);
		close(save_fd->pipe2[0]);
		save_fd->pipe2[0] = -1;
	}
	if (save_fd->redirs != 1 && save_fd->redirs != 3)
	{
		dup2(save_fd->pipe1[1], STDOUT_FILENO);
		close(save_fd->pipe1[1]);
		save_fd->pipe1[1] = -1;
	}
}

void	last_cmd(t_pipe *save_fd)
{
	if (save_fd->index % 2 == 1)
	{
		if (save_fd->redirs != 2 && save_fd->redirs != 3)
		{
			dup2(save_fd->pipe1[0], STDIN_FILENO);
			close(save_fd->pipe1[0]);
			save_fd->pipe1[0] = -1;
		}
		if (save_fd->redirs != 1 && save_fd->redirs != 3)
			dup2(save_fd->std_fd[1], STDOUT_FILENO);
	}
	else
	{
		if (save_fd->redirs != 2 && save_fd->redirs != 3)
		{
			dup2(save_fd->pipe1[0], STDIN_FILENO);
			close(save_fd->pipe1[0]);
			save_fd->pipe1[0] = -1;
		}
		if (save_fd->redirs != 1 && save_fd->redirs != 3)
			dup2(save_fd->std_fd[1], STDOUT_FILENO);
	}
}

void	manage_pipe(t_pipe *save_pipe)
{
	if (save_pipe->index == 0 && save_pipe->nmb_max_cmd > 1)
			first_cmd(save_pipe);
	else if (save_pipe->index > 0 && save_pipe->index < save_pipe->nmb_max_cmd - 1)
	{
		if (save_pipe->index % 2 == 1)
			other_cmd(save_pipe);
		else
			other_cmd_pair(save_pipe);
	}
	else if (save_pipe->index == save_pipe->nmb_max_cmd - 1)
		last_cmd(save_pipe);
}

void	child(t_command_line *cmd_line, t_pipe *save_pipe, t_list *envp, pid_t **tforks)
{
	close_pipe(save_pipe);
	close(save_pipe->std_fd[0]);
	close(save_pipe->std_fd[1]);
	free(*tforks);
	if (!cmd_line->error_code)
		cmd_line->return_value = main_execution(cmd_line->commands, envp, save_pipe, 1);
	else
		cmd_line->return_value = cmd_line->error_code;
	free(envp);
	exit(1);
}

pid_t	_pipe(t_pipe *save_pipe, t_command_line *cmd_line, t_list *envp, pid_t **saveforks)
{
	pid_t	tforks;

	if (open_pipe(save_pipe) == -1)
		return (-1);
	tforks = fork();
	if (tforks == -1)
		return (close_pipe(save_pipe));
	save_pipe->redirs = main_redirection(cmd_line, save_pipe->std_fd, envp);
	manage_pipe(save_pipe);
	if (!tforks)
		child(cmd_line, save_pipe, envp, saveforks);
	return (tforks);
}

void	init_save_pipe(t_pipe *save_pipe, t_command *commands)
{
	save_pipe->pipe1[0] = -1;
	save_pipe->pipe2[0] = -1;
	save_pipe->nmb_max_cmd = ft_lst_command_size(commands);
	save_pipe->index = 0;
	save_pipe->std_fd[0] = dup(STDIN_FILENO);
	save_pipe->std_fd[1] = dup(STDOUT_FILENO);
}

int	main_pipe(t_command_line *cmd_line, t_list **envp)
{
	t_pipe	*save_pipe;
	pid_t	*tforks;
	int		i;

	save_pipe = NULL;
	init_save_pipe(save_pipe, cmd_line->commands);
	tforks = ft_calloc(save_pipe->nmb_max_cmd, sizeof(pid_t));
	while (cmd_line->commands)
	{
		tforks[save_pipe->index] = _pipe(save_pipe, cmd_line, *envp, &tforks);
		cmd_line->commands = cmd_line->commands->next;
		save_pipe->index++;
	}
	i = 0;
	while (tforks[i])
	{
		if (tforks[i] != -1)
			waitpid(tforks[i], &cmd_line->return_value, 0);
		i++;
	}
	return (0);
}







// void	management_fd(t_pipe *save_fd, int i)
// {
// 	if (i == 0)
// 	{
// 		dup2(save_fd->std_fd[0], STDIN_FILENO);
// 		dup2(save_fd->pipe[1], STDOUT_FILENO);
// 	}
// 	if (i == save_fd->nmb_max_cmd - 1)
// 	{
// 		dup2(save_fd->previous, STDIN_FILENO);
// 		dup2(save_fd->std_fd[1], STDOUT_FILENO);
// 		close(save_fd->previous);
// 	}
// 	else if (i > 0)
// 	{
// 		dup2(save_fd->previous, STDIN_FILENO);
// 		dup2(save_fd->pipe[1], STDOUT_FILENO);
// 		close(save_fd->previous);
// 	}
// 	else if (i == -1)
// 	{
// 		dup2(save_fd->std_fd[0], STDIN_FILENO);
// 		dup2(save_fd->std_fd[1], STDOUT_FILENO);
// 	}	// write(1, "coucou\n", 8);
// }

// int	free_and_close(t_pipe *fds, t_command_line *line, t_int_list *pid, t_list **env)
// {
// 	if(env && *env)
// 		ft_lstclear(env, free);
// 	if (line)
// 		free_struct(line);
// 	if (ft_int_lstsize(pid) < fds->nmb_max_cmd)
// 		fds->previous = dup(fds->pipe[0]);
// 	if (pid)
// 		ft_int_lstclear(&pid);
// 	close(fds->pipe[0]);
// 	close(fds->pipe[1]);
// 	dup2(fds->std_fd[0], STDIN_FILENO);
// 	dup2(fds->std_fd[1], STDOUT_FILENO);
// 	return (0);
// }

// int	main_pipe(t_command_line *cmd_line, t_list **envp)
// {
// 	int			error;
// 	t_pipe		pipe_fds;
// 	t_command_line	*current;
// 	t_int_list		*forks;
// 	t_int_list		*new_elemt;
// 	t_int_list		*to_remove;

// 	signal(SIGINT, _sigint_exec);

// 	forks = NULL;
// 	error = 0;
// 	pipe_fds.previous = 0;
// 	pipe_fds.std_fd[0] = dup(STDIN_FILENO);
// 	pipe_fds.std_fd[1] = dup(STDOUT_FILENO);
// 	pipe_fds.nmb_max_cmd = ft_lst_command_size(cmd_line->commands);
// 	current = cmd_line;
// 	if (pipe_fds.nmb_max_cmd == 1)
// 	{
// 		pipe_fds.pipe[0] = 0;
// 		main_redirection(cmd_line, pipe_fds.std_fd, *envp);
// 		cmd_line->return_value = main_execution(current->commands, *envp, &pipe_fds, 0);
// 		close(pipe_fds.std_fd[0]);
// 		close(pipe_fds.std_fd[1]);
// 		return(cmd_line->return_value);
// 	}
// 	while (current->commands)
// 	{
// 		if (pipe(pipe_fds.pipe))
// 			return (free_and_close(&pipe_fds, cmd_line, forks, NULL));
// 		new_elemt = ft_int_lstnew(fork());
// 		if (!new_elemt)
// 			return (free_and_close(&pipe_fds, cmd_line, forks, NULL));
// 		if ((pid_t) (new_elemt->content) == 0)
// 		{
// 			management_fd(&pipe_fds, ft_int_lstsize(forks));
// 			main_redirection(cmd_line, pipe_fds.std_fd, *envp);
// 			if (!cmd_line->error_code)
// 				cmd_line->return_value = main_execution(current->commands, *envp, &pipe_fds, 1);
// 			else
// 				cmd_line->return_value = cmd_line->error_code;
// 			free_and_close(&pipe_fds, cmd_line, NULL, NULL);
			
			
// 			close(pipe_fds.std_fd[0]);
// 			close(pipe_fds.std_fd[1]);
// 			close(pipe_fds.previous);
// 			exit(cmd_line->return_value);
// 		}
// 		else if ((pid_t)(new_elemt->content) > 0)
// 		{
// 			if (cmd_line->error_code)
// 			{
// 				error = cmd_line->error_code;
// 				cmd_line->error_code = 0;
// 			}
// 			ft_int_lstadd_back(&forks, new_elemt);
// 			if (pipe_fds.previous)
// 				close(pipe_fds.previous);
// 			free_and_close(&pipe_fds, NULL, NULL, NULL);
// 			current->commands = current->commands->next;
// 		}
// 	}

// 	// new_elemt = forks;
// 	close(pipe_fds.std_fd[0]);
// 	close(pipe_fds.std_fd[1]);
// 	free_and_close(&pipe_fds, NULL, NULL, NULL);
// 	while (ft_int_lstsize(forks))
// 	{
// 		printf("len = %d\n", ft_int_lstsize(forks));
// 		to_remove = NULL;
// 		// printf("DHUIAWDHA\n");
// 		forks->content = waitpid(((pid_t) forks->content), &error, 0);
// 		// printf("AAAAAAAA\n");
// 		if (WIFSIGNALED(error))
// 		{
// 			// printf("BBBBBB\n");
// 			if (WTERMSIG(error))
// 			{
// 				printf("Sig: %d\n", WTERMSIG(error) + 128);
// 			}
// 		}
// 		else if (WIFEXITED(error))
// 		{
// 			printf("Exited!\n");
// 			cmd_line->return_value = WEXITSTATUS(error);
// 		}
// 		if ((pid_t)(forks->content) <= 0)
// 			to_remove = forks;
// 		// if (!forks->next)
// 			// forks = new_elemt;
// 		// else
// 		forks = forks->next;
// 		if(to_remove)
// 			ft_int_lst_remove_index(&forks, ft_int_lst_get_index(forks, to_remove));
// 	}
// 	close(pipe_fds.std_fd[0]);
// 	close(pipe_fds.std_fd[1]);
// 	signal(SIGINT, _sigint);
// 	return (error);
// }

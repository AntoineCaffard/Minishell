/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:27 by utilisateur       #+#    #+#             */
/*   Updated: 2024/04/24 14:19:08 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	management_fd(t_pipe *save_fd, int i)
{
	if (i == 0)
	{
		dup2(save_fd->save_first_fd[0], STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	}
	if (i == save_fd->nmb_max_cmd - 1)
	{
		dup2(save_fd->save_fd, STDIN_FILENO);
		dup2(save_fd->save_first_fd[1], STDOUT_FILENO);
	}
	else if (i > 0)
	{
		dup2(save_fd->save_fd, STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	}
	else if (i == -1)
	{
		dup2(save_fd->save_first_fd[0], STDIN_FILENO);
		dup2(save_fd->save_first_fd[1], STDOUT_FILENO);
		close(save_fd->save_first_fd[0]);
		close(save_fd->save_first_fd[1]);
	}
}

int	ft_lst_command_size(t_command *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_lst_command_size(lst->next));
}

void	_pipe(t_command_line *cmd_line, t_list **envp, t_pipe *save_fd)
{
	int	i;
	int	j;
	int	error = 0;
	pid_t	tfork[save_fd->nmb_max_cmd];

	i = 0;
	while (cmd_line->commands)
	{
		if (pipe(save_fd->pipe))
			return ;
		if (i <= save_fd->nmb_max_cmd)
			tfork[i] = fork();
		main_redirection(cmd_line);
		if (!tfork[i])
		{
			management_fd(save_fd, i);
			error = main_execution(cmd_line, *envp);
			if (save_fd->save_fd > -1)
				close(save_fd->save_fd);
			close(save_fd->pipe[0]);
			close(save_fd->pipe[1]);
			close(save_fd->save_first_fd[1]);
			close(save_fd->save_first_fd[0]);
			exit (error);
		}
		else if (tfork[i] > 0) {
			if (save_fd->save_fd > -1)
				close(save_fd->save_fd);
			save_fd->save_fd = dup(save_fd->pipe[0]);
			close(save_fd->pipe[0]);
			close(save_fd->pipe[1]);
			cmd_line->commands = cmd_line->commands->next;
			i++;
		}
	}
	j = 0;
	while (j < i && tfork[j] != -1)
	{
		waitpid(tfork[j++], &error, 0);
		cmd_line->return_value = WEXITSTATUS(error);
	}
	if (save_fd->save_fd > -1)
		close(save_fd->save_fd);
}

void	main_pipe(t_command_line *cmd_line, t_list **envp)
{
	t_pipe	save_fd;

	save_fd.save_first_fd[0] = dup(STDIN_FILENO);
	save_fd.save_first_fd[1] = dup(STDOUT_FILENO);
	save_fd.nmb_max_cmd = ft_lst_command_size(cmd_line->commands);
	save_fd.save_fd = -1;
	if (save_fd.nmb_max_cmd == 1)
	{
		main_redirection(cmd_line);
		cmd_line->return_value = main_execution(cmd_line, *envp);
	}
	else
		_pipe(cmd_line, envp, &save_fd);
	management_fd(&save_fd, -1);
	close (save_fd.save_first_fd[0]);
	close (save_fd.save_first_fd[1]);
}

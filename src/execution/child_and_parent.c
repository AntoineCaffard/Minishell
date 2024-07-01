/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:36:46 by trebours          #+#    #+#             */
/*   Updated: 2024/07/01 13:36:53 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent(t_pipe *fds, t_cmdline *cmd_line, pid_t *pid)
{
	waitpid(pid[fds->index], &cmd_line->return_value, 0);
	if (cmd_line->return_value == 126 || cmd_line->return_value == 127)
		;
	else if (WIFSIGNALED(cmd_line->return_value))
		cmd_line->return_value = WTERMSIG(cmd_line->return_value) + 128;
	else if (WIFEXITED(cmd_line->return_value))
		cmd_line ->return_value = WEXITSTATUS(cmd_line->return_value);
	fds->index--;
	while (fds->index >= 0)
	{
		waitpid(pid[fds->index], &cmd_line->return_value, 0);
		fds->index--;
	}
}

void	child(t_cmdline *cmd_line, t_pipe *fds, t_list **envp, pid_t *pid)
{
	int	error;

	error = 0;
	free(pid);
	main_redirection(cmd_line, fds->std_fd, *envp);
	gestion_pipe(fds, cmd_line->cmds->redirs);
	close_pipe(fds);
	if (!cmd_line->error_code)
	{
		error = main_execution(cmd_line->cmds, *envp, fds, 1);
		cmd_line->cmds = fds->save;
		free_struct(cmd_line);
		ft_lstclear(envp, free);
		clear_history();
		exit(error);
	}
	clear_history();
	free_struct(cmd_line);
	exit(cmd_line->error_code);
}

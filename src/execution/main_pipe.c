/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:05:23 by trebours          #+#    #+#             */
/*   Updated: 2024/07/22 10:08:43 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_pipe(t_pipe *save_fd, t_cmdlist *cmd)
{
	int	i;

	save_fd->nmb_max_cmd = ft_cmdsize(cmd);
	if (save_fd->nmb_max_cmd == 1)
		return (1);
	save_fd->pipe = ft_calloc(3, sizeof(int *));
	if (!save_fd->pipe)
		return (-1);
	i = 0;
	while (i < 2)
	{
		save_fd->pipe[i] = ft_calloc(2, sizeof(int));
		pipe(save_fd->pipe[i]);
		i++;
	}
	return (0);
}

void	close_pipe(t_pipe *fds)
{
	int	i;

	i = 0;
	while (fds->pipe[i])
	{
		if (fds->pipe[i][0] != -1)
			close(fds->pipe[i][0]);
		if (fds->pipe[i][1] != -1)
			close(fds->pipe[i][1]);
		free(fds->pipe[i]);
		i++;
	}
	close(fds->std_fd[0]);
	close(fds->std_fd[1]);
	free(fds->pipe);
}

void	verif_pipe(t_pipe *fds)
{
	int	index;

	if (!fds->index)
	{
		if (fds->pipe[0][1] != -1)
			close(fds->pipe[0][1]);
		fds->pipe[0][1] = -1;
		return ;
	}
	if (fds->index % 2)
		index = 1;
	else
		index = 0;
	if (fds->pipe[index][1] != -1)
		close(fds->pipe[index][1]);
	fds->pipe[index][1] = -1;
	if (index == 0)
		index++;
	else
		index--;
	if (fds->pipe[index][0] != -1)
		close(fds->pipe[index][0]);
	fds->pipe[index][0] = -1;
	if (fds->pipe[0][0] == -1 && fds->pipe[0][1] == -1)
		pipe(fds->pipe[0]);
	if (fds->pipe[1][0] == -1 && fds->pipe[1][1] == -1)
		pipe(fds->pipe[1]);
}

static void	multi_pipe(t_pipe *fds, t_cmdline *cmd_line, t_list **envp)
{
	pid_t	*pid;

	pid = ft_calloc(fds->nmb_max_cmd, sizeof(pid_t));
	fds->save = cmd_line->cmds;
	while (fds->index < fds->nmb_max_cmd)
	{
		pid[fds->index] = fork();
		if (pid[fds->index] == 0)
			child(cmd_line, fds, envp, pid);
		verif_pipe(fds);
		fds->index++;
		cmd_line->cmds = cmd_line->cmds->next;
	}
	close_pipe(fds);
	fds->index--;
	parent(fds, cmd_line, pid);
	free(pid);
}

static int	single_cmd(t_cmdline *cmd_line, t_pipe save_fd, t_list **envp)
{
	int	i;

	i = 0;
	main_redirection(cmd_line);
	if (!cmd_line->error_code && cmd_line->cmds->args)
	{
		i = main_execution(cmd_line->cmds, *envp, &save_fd, 0);
		cmd_line->return_code = i;
	}
	else
		cmd_line->return_code = cmd_line->error_code;
	dup2(save_fd.std_fd[0], STDIN_FILENO);
	dup2(save_fd.std_fd[1], STDOUT_FILENO);
	close(save_fd.std_fd[0]);
	close(save_fd.std_fd[1]);
	signal(SIGINT, _sigint);
	return (i);
}

int	main_pipe(t_cmdline *cmd_line, t_list **envp)
{
	int		i;
	t_pipe	save_fd;

	(void)envp;
	signal(SIGINT, _sigint_exec);
//	signal(SIGQUIT,SIG_DFL);
	save_fd.index = 0;
	save_fd.std_fd[1] = dup(STDIN_FILENO);
	save_fd.std_fd[0] = dup(STDOUT_FILENO);
	i = init_pipe(&save_fd, cmd_line->cmds);
	if (i == 1)
		return (single_cmd(cmd_line, save_fd, envp));
	else if (i == -1)
		return (-1);
	else
		multi_pipe(&save_fd, cmd_line, envp);
	dup2(save_fd.std_fd[0], STDIN_FILENO);
	dup2(save_fd.std_fd[1], STDOUT_FILENO);
	signal(SIGINT, _sigint);
//	signal(SIGQUIT, SIG_IGN);
	return (1);
}

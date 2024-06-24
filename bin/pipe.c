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
	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	return (1 + ft_lst_command_size(lst->next));
}

int	init_pipe(t_pipe *save_fd, t_command *cmd)
{
	int	n;
	int	i;

	save_fd->nmb_max_cmd = ft_lst_command_size(cmd);
	n = save_fd->nmb_max_cmd -1;
	if (n == 0)
		return (1);
	save_fd->pipe = ft_calloc(n + 1, sizeof(int*));
	if (!save_fd->pipe)
		return (-1);
	i = 0;
	while (i < n)
	{
		save_fd->pipe [i] = ft_calloc(2, sizeof(int));
		pipe(save_fd->pipe[i]);
		i++;
	}
	return(0);
}

void	gestion_pipe(t_pipe *fds, t_redir *redirs)
{
	if (fds->index == 0)
	{
		if (!redirs || (redirs->type != REDIRECTION_APPEND && redirs->type != REDIRECTION_OUTFILE))
		{
			dup2(fds->pipe[fds->index][1], STDOUT_FILENO);
			close(fds->pipe[fds->index][1]);
			fds->pipe[fds->index][1] = -1;
		}
		else
		{
			close(fds->pipe[fds->index][1]);
			fds->pipe[fds->index][1] = -1;
		}
		close(fds->pipe[fds->index][0]);
		fds->pipe[fds->index][0] = -1;
	}
	else if (fds->index == fds->nmb_max_cmd - 1)
	{
		// if (!redirs || (redirs->type != REDIRECTION_APPEND && redirs->type != REDIRECTION_OUTFILE))
			// dup2(fds->std_fd[1], STDOUT_FILENO);
		if (!redirs || (redirs->type != REDIRECTION_INFILE && redirs->type != REDIRECTION_HEREDOC))
		{
			dup2(fds->pipe[fds->index - 1][0], STDIN_FILENO);
			close(fds->pipe[fds->index - 1][0]);
			fds->pipe[fds->index - 1][0] = -1;
		}
		else
		{
			close (fds->pipe[fds->index - 1][0]);
			fds->pipe[fds->index - 1][0] = -1;
		}
	}
	else if (fds->index < fds->nmb_max_cmd - 1)
	{
		if (!redirs || (redirs->type != REDIRECTION_APPEND && redirs->type != REDIRECTION_OUTFILE))
		{
			dup2(fds->pipe[fds->index][1], STDOUT_FILENO);
			close(fds->pipe[fds->index][1]);
			fds->pipe[fds->index][1] = -1;
		}
		else
		{
			close(fds->pipe[fds->index][1]);
			fds->pipe[fds->index][1] = -1;
		}
		if (!redirs || (redirs->type != REDIRECTION_INFILE && redirs->type != REDIRECTION_HEREDOC))
		{
			dup2(fds->pipe[fds->index - 1][0], STDIN_FILENO);
			close(fds->pipe[fds->index -1][0]);
			fds->pipe[fds->index - 1 ][0] = -1;
		}
		else
		{
			close(fds->pipe[fds->index -1][0]);
			fds->pipe[fds->index - 1 ][0] = -1;
		}
	}
}

void close_pipe(t_pipe *fds)
{
	int i;

	i = 0;
	while (fds->pipe[i])
	{
		if (fds->pipe[i][0] != -1)
			close(fds->pipe[i][0]);
		if (fds->pipe[i][1] != -1)
			close(fds->pipe[i][1]);
		i++;
	}
	close(fds->std_fd[0]);
	close(fds->std_fd[1]);
	free(fds->pipe);
}

void	multi_pipe(t_pipe *fds, t_command_line *cmd_line, t_list **envp)
{
	pid_t *pid;

	pid = ft_calloc(fds->nmb_max_cmd, sizeof(pid_t));
	while (fds->index < fds->nmb_max_cmd)
	{
		pid[fds->index] = fork();
		if (pid[fds->index] == 0)
		{
			gestion_pipe(fds, cmd_line->commands->redirs);
			main_redirection(cmd_line, fds->std_fd, *envp);
			close_pipe(fds);
			main_execution(cmd_line->commands, *envp, fds, 1);
			exit(1);
		}
		// printf("\033[0;32mNew Pid: %d\033[0;m\n", pid[fds->index]);
		fds->index++;
		cmd_line->commands = cmd_line->commands->next;
	}
	close_pipe(fds);
	fds->index--;
	while (fds->index >= 0)
	{
		// printf("\033[1;31mWaiting for pid: %d\033[0;m\n", pid[fds->index]);
		waitpid(pid[fds->index], &cmd_line->return_value, 0);
		// printf("\033[1;36mPid is finish: %d\033[0;m\n", pid[fds->index]);
		if (WIFSIGNALED(cmd_line->return_value))
			cmd_line->return_value = WTERMSIG(cmd_line->return_value) + 128;
		else if (WIFEXITED(cmd_line->return_value))
			cmd_line->return_value = WEXITSTATUS(cmd_line->return_value);
		fds->index--;
	}
	return ;
}

int	main_pipe(t_command_line *cmd_line, t_list **envp)
{
	int	i;
	t_pipe	save_fd;
	
	(void)envp;
	signal(SIGINT, _sigint_exec);
	save_fd.index = 0;
	save_fd.std_fd[1] = dup(STDIN_FILENO);
	save_fd.std_fd[0] = dup(STDOUT_FILENO);
	i = init_pipe(&save_fd, cmd_line->commands);
	if (i == 1)
	{
		main_redirection(cmd_line, save_fd.std_fd, *envp);
		i = main_execution(cmd_line->commands, *envp, &save_fd, 0);
		cmd_line->return_value = i;
		close(save_fd.std_fd[0]);
		close(save_fd.std_fd[1]);
		signal(SIGINT, _sigint);
		return (i);
	}
	else if (i == -1)
		return (-1);
	else
		multi_pipe(&save_fd, cmd_line, envp);
	dup2(save_fd.std_fd[0], STDIN_FILENO);
	dup2(save_fd.std_fd[1], STDOUT_FILENO);
	signal(SIGINT, _sigint);
	return(1);
}

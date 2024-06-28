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
	save_fd->pipe = ft_calloc(n + 1, sizeof(int *));
	if (!save_fd->pipe)
		return (-1);
	i = 0;
	while (i < n)
	{
		save_fd->pipe [i] = ft_calloc(2, sizeof(int));
		pipe(save_fd->pipe[i]);
		i++;
	}
	return (0);
}

void	gestion_pipe(t_pipe *fds, t_redir *redirs)
{
	if (fds->index == 0)
	{
		if (!redirs || (redirs->type != REDIRECTION_APPEND
				&& redirs->type != REDIRECTION_OUTFILE))
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
		if (!redirs || (redirs->type != REDIRECTION_INFILE
				&& redirs->type != REDIRECTION_HEREDOC))
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
		if (!redirs || (redirs->type != REDIRECTION_APPEND
				&& redirs->type != REDIRECTION_OUTFILE))
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
		if (!redirs || (redirs->type != REDIRECTION_INFILE
				&& redirs->type != REDIRECTION_HEREDOC))
		{
			dup2(fds->pipe[fds->index - 1][0], STDIN_FILENO);
			close(fds->pipe[fds->index -1][0]);
			fds->pipe[fds->index - 1][0] = -1;
		}
		else
		{
			close(fds->pipe[fds->index -1][0]);
			fds->pipe[fds->index - 1][0] = -1;
		}
	}
} // more 25 line

void	parent(t_pipe *fds, t_command_line *cmd_line, pid_t *pid)
{
	waitpid(pid[fds->index], &cmd_line->return_value, 0);
	if (cmd_line->return_value == 126 || cmd_line->return_value == 127);
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
		i++;
	}
	close(fds->std_fd[0]);
	close(fds->std_fd[1]);
	free(fds->pipe);
}

void	child(t_command_line *cmd_line, t_pipe *fds, t_list **envp)
{
	int	error;

	error = 0;
	main_redirection(cmd_line, fds->std_fd, *envp);
	gestion_pipe(fds, cmd_line->commands->redirs);
	close_pipe(fds);
	if (!cmd_line->error_code)
	{
		error = main_execution(cmd_line->commands, *envp, fds, 1);
		exit(error);
	}
	exit(cmd_line->error_code);
}

void	multi_pipe(t_pipe *fds, t_command_line *cmd_line, t_list **envp)
{
	pid_t	*pid;
	int		error;

	pid = ft_calloc(fds->nmb_max_cmd, sizeof(pid_t));
	while (fds->index < fds->nmb_max_cmd)
	{
		pid[fds->index] = fork();
		if (pid[fds->index] == 0)
			child(cmd_line, fds, envp);
		fds->index++;
		cmd_line->commands = cmd_line->commands->next;
	}
	close_pipe(fds);
	fds->index--;
	parent(fds, cmd_line, pid);
}

int	single_cmd(t_command_line *cmd_line, t_pipe save_fd, t_list **envp)
{
	int	i;

	i = 0;
	main_redirection(cmd_line, save_fd.std_fd, *envp);
	if (!cmd_line->error_code)
	{
		i = main_execution(cmd_line->commands, *envp, &save_fd, 0);
		cmd_line->return_value = i;
	}
	else
		cmd_line->return_value = cmd_line->error_code;
	dup2(save_fd.std_fd[0], STDIN_FILENO);
	close(save_fd.std_fd[0]);
	close(save_fd.std_fd[1]);
	signal(SIGINT, _sigint);
	return (i);
}

int	main_pipe(t_command_line *cmd_line, t_list **envp)
{
	int		i;
	t_pipe	save_fd;

	(void)envp;
	signal(SIGINT, _sigint_exec);
	save_fd.index = 0;
	save_fd.std_fd[1] = dup(STDIN_FILENO);
	save_fd.std_fd[0] = dup(STDOUT_FILENO);
	i = init_pipe(&save_fd, cmd_line->commands);
	if (i == 1)
		return (single_cmd(cmd_line, save_fd, envp));
	else if (i == -1)
		return (-1);
	else
		multi_pipe(&save_fd, cmd_line, envp);
	dup2(save_fd.std_fd[0], STDIN_FILENO);
	dup2(save_fd.std_fd[1], STDOUT_FILENO);
	signal(SIGINT, _sigint);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:43:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 14:05:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_search;
	unsigned char	*s2_search;

	s1_search = (unsigned char *) s1;
	s2_search = (unsigned char *) s2;
	while (*s1_search && *s1_search == *s2_search)
	{
		s1_search++;
		s2_search++;
	}
	return ((int) *s1_search - (int) *s2_search);
}

void	heredoc(char **params, t_list **envp)
{
	char	*line;
	char	*limiter;
	int		fds[2];
	int		pipe_fds[2];
	int		fst_command;

	if (ft_strlen(params[0]) > 2)
	{
		limiter = &(params[0][2]);
		fst_command = 1;
	}
	else if (!params[1])
		return ;
	else
	{
		limiter = params[1];
		fst_command = 2;
	}
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
	line = ft_calloc(1, sizeof(char));
	pipe(pipe_fds);
	while (ft_strcmp(line, limiter) != 0)
	{
		free(line);
		line = readline("\033[1;33mheredoc: \033[0;m");
		dup2(pipe_fds[1], STDOUT_FILENO);
		if (ft_strcmp(line, limiter) != 0)
			printf("%s\n", line);
		dup2(fds[1], STDOUT_FILENO);
	}
	dup2(pipe_fds[1], STDOUT_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	if (!params[fst_command])
		return ;
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[1]);
	ft_start_minishell(&(params[fst_command]), envp);
	close(pipe_fds[0]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}


void	heredoc_pipe(char **params, t_list **envp, t_pipe *my_pipe)
{
	char	*line;
	char	*limiter;
	int		fst_command;

	if (ft_strlen(params[0]) > 2)
	{
		limiter = &(params[0][2]);
		fst_command = 1;
	}
	else if (!params[1])
		return ;
	else
	{
		limiter = params[1];
		fst_command = 2;
	}
	line = ft_calloc(1, sizeof(char));
	while (ft_strcmp(line, limiter) != 0)
	{
		free(line);
		line = readline("\033[1;33mheredoc: \033[0;m");
		dup2(my_pipe->pipe[1], STDOUT_FILENO);
		if (ft_strcmp(line, limiter) != 0)
			printf("%s\n", line);
		dup2(my_pipe->save_first_fd[1], STDOUT_FILENO);
	}
	dup2(my_pipe->pipe[1], STDOUT_FILENO);
	dup2(my_pipe->save_first_fd[1], STDOUT_FILENO);
	if (!params[fst_command])
		return ;
	dup2((my_pipe->pipe)[0], STDIN_FILENO);
	close(my_pipe->pipe[1]);
	ft_start_minishell(&(params[fst_command]), envp);
	close(my_pipe->pipe[0]);
	dup2(my_pipe->save_first_fd[0], STDIN_FILENO);
	close(my_pipe->save_first_fd[0]);
}

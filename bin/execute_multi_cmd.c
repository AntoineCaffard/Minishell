/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:52:54 by trebours          #+#    #+#             */
/*   Updated: 2024/06/17 09:52:57 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	multi_command(char **cmd, char **envp, t_pipe *pipe_fds)
{
	(void)pipe_fds;
	if (execve(cmd[0], cmd, envp))
	{
		ft_free_stringtab(envp);
		perror("execve");
		exit (1);
	}
	return (1);
}

int	execute_multi(char **line, t_list *t_envp, t_pipe *pipe_fds)
{
	char		**path;
	char		**envp;
	int			error;
	struct stat	buf;

	path = init_path(t_envp);
	error = 0;
	if (ft_strchr(line[0], '/'))
	{
		if (stat(line[0], &buf))
		{
			display_error("file or directory not found", line[0]);
			return (127);
		}
		if ((buf.st_mode != S_IXUSR))
		{
			display_error("Permission denied", line[0]);
			return (126);
		}
		if (S_ISDIR(buf.st_mode))
		{
			display_error("Is a directory", line[0]);
			return (127);
		}
	}
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path, &error);
	if (!line[0] || error > 0)
	{
		if (path)
			ft_free_stringtab(path);
		return (1);
	}
	envp = init_t_list_in_stringtab(t_envp);
	error = multi_command(line, envp, pipe_fds);
	ft_free_stringtab(path);
	return (error);
}

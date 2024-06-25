/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_other_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:53:28 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 08:59:44 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*init_link(char *src, char **path, int *error)
{
	char	*verif_link;
	char	*save;
	int		i;
	struct stat	buf;

	if (!src || !path)
		return (NULL);
	i = 0;
	save = ft_strjoin("/", src);
	stat(save, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		display_error("Is a directory", &save[1]);
		*error = 126;
		return (NULL);
	}
	while (path[i])
	{
		verif_link = ft_strjoin(path[i], save);
		if (access(verif_link, X_OK) == 0)
		{
			free(src);
			free(save);
			return (verif_link);
		}
		i++;
		free(verif_link);
	}
	free(save);
	display_error("command not found", src);
	*error = 127;
	free(src);
	return (NULL);
}

char	**init_path(t_list *envp)
{
	char	*path;
	char	**res;

	path = NULL;
	if (!envp)
		return (NULL);
	while (envp)
	{
		if (ft_strnstr((char *)envp->content, "PATH\0", 4))
			path = (char *)envp->content;
		envp = envp->next;
	}
	if (!path)
		return (NULL);
	res = ft_split_str(path, ":");
	return (res);
}

int	command_n(char **cmd, char **envp, t_pipe *pipe_fds)
{
	pid_t	tfork;
	int		error;

	tfork = fork();
	error = 0;
	if (tfork < 0)
		return (1);
	if (tfork == 0)
	{
		close(pipe_fds->std_fd[0]);
		close(pipe_fds->std_fd[1]);
		if (execve(cmd[0], cmd, envp))
		{
			ft_free_stringtab(envp);
			perror("execve");
			exit (1);
		}
	}
	else
	{
		ft_free_stringtab(envp);
		dup2(pipe_fds->std_fd[0], STDIN_FILENO);
		dup2(pipe_fds->std_fd[1], STDOUT_FILENO);
		while (waitpid(tfork, &error, 0) != -1)
			continue ;
		if (WIFSIGNALED(error))
			return (WTERMSIG(error) + 128);
		return (WEXITSTATUS(error));
	}
	return (error);
}

int	execute_command(char **line, t_list *t_envp, t_pipe *pipe_fds)
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
			return (126);
		}
	}
	else if (access(line[0], X_OK))
		line[0] = init_link(line[0], path, &error);
	if (!line[0] || error > 0)
	{
		if (path)
			ft_free_stringtab(path);
		return (error);
	}
	envp = init_t_list_in_stringtab(t_envp);
	error = command_n(line, envp, pipe_fds);
	ft_free_stringtab(path);
	return (error);
}

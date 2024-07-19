/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:14:29 by trebours          #+#    #+#             */
/*   Updated: 2024/07/01 16:47:47 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_link(char *src, char **path, int *error)
{
	char	*verif_link;
	char	*save;
	int		i;

	if (!src || !path)
		return (NULL);
	i = 0;
	save = ft_strjoin("/", src);
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
	write(2, "command not found\n", 19);
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
	res = ft_split_str(&path[5], ":");
	return (res);
}

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

	path = init_path(t_envp);
	error = 0;
	if (ft_strchr(line[0], '/'))
	{
		error = verif_stat(line, path);
		if (error)
			return (error);
	}
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path, &error);
	if (!line[0] || error > 0)
	{
		if (path)
			ft_free_stringtab(path);
		return (1);
	}
	envp = tabify_list(t_envp);
	error = multi_command(line, envp, pipe_fds);
	ft_free_stringtab(path);
	return (error);
}

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

char	*init_link(char *src, char **path)
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
	display_error("command not found", src);
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

int	command_n(char **cmd, char **envp)
{
	pid_t	tfork;
	int		error;

	tfork = fork();
	error = 0;	
	if (tfork < 0)
		return (1);
	if (tfork == 0)
	{
		if (execve(cmd[0], cmd, envp))
		{
			ft_free_stringtab(envp);
			perror("execve");
			return (-1);
		}
	}
	else
	{
		ft_free_stringtab(envp);
		while (waitpid(-1, &error, 0) != -1)
			continue ;
		if (error > 0)
			return (error);
	}
	return (0);
}

int	execute_command(char **line, t_list *t_envp)
{
	char	**path;
	char	**envp;
	int		fd;
	int		error;

	fd = dup(STDOUT_FILENO);
	path = init_path(t_envp);
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path);
	if (!line[0])
	{
		if (path)
			ft_free_stringtab(path);
		close(fd);
		return (1);
	}
	envp = init_t_list_in_stringtab(t_envp);
	error = command_n(line, envp);
	ft_free_stringtab(path);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (error);
}

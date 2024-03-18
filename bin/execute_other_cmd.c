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

void	command_n(char **cmd, t_list *lst_envp)
{
	pid_t	tfork;
	char	**envp;

	envp = init_t_list_in_stringtab(lst_envp);
	tfork = fork();
	if (tfork < 0)
		return ;
	if (tfork == 0)
	{
		if (execve(cmd[0], cmd, envp))
		{
			ft_free_stringtab(cmd);
			ft_free_stringtab(envp);
			perror("execve");
		}
	}
	else
	{
		ft_free_stringtab(envp);
		while (waitpid(-1, NULL, 0) != -1)
			continue ;
	}
}

void	execute_command(char **line, t_list *envp)
{
	char	**path;
	int		fd;

	fd = dup(STDOUT_FILENO);
	path = init_path(envp);
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path);
	if (!line[0])
	{
		if (path)
			ft_free_stringtab(path);
		close(fd);
		return ;
	}
	command_n(line, envp);
	ft_free_stringtab(path);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

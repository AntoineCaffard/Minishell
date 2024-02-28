/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_other_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:53:28 by trebours          #+#    #+#             */
/*   Updated: 2024/02/28 10:33:45 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*init_link(char *src, char **path)
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
	dup2(2, 1);			// fonction message erreur ?
	ft_printf("minishell: %s: command not found\n", src);
	return (NULL);
}

char	**init_path(t_list *envp)
{
	char	*path;
	char	**res;

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
			perror("execve");
			ft_free_stringtab(cmd);
			ft_free_stringtab(envp);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		ft_free_stringtab(envp);
	}
}

void	execute_command(char **line, t_list *envp)
{
	char	**path;

	path = init_path(envp);
	if (!path)
		return ;
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path);
	if (!line[0])
		return ;
	command_n(line, envp);
	ft_free_stringtab(path);
}

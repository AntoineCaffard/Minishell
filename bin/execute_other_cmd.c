/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_other_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:53:28 by trebours          #+#    #+#             */
/*   Updated: 2024/02/28 11:24:58 by trebours         ###   ########.fr       */
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
	dup2(2, STDOUT_FILENO);			// fonction message erreur ?
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
			ft_free_stringtab(cmd);
			ft_free_stringtab(envp);
			perror("execve");
		}
		printf("test\n\n\n\n");
		// exit(1);
	}
	else
	{
		ft_free_stringtab(envp);
		while (waitpid(-1, NULL, 0) != -1)
			continue ;
	}
}

int	check_command(char **line, char **path, t_list *envp)
{
	int	fd;
	int	save_fd;

	if (!ft_strncmp(line[0], "<", ft_strlen(line[0])))
	{
		save_fd = dup(STDIN_FILENO);
		fd = open(line[1], O_RDONLY);
		if (fd == -1)
		{
			printf("%s: file no found\n", line[1]);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		if (access(line[2], X_OK))
			line[2] = init_link(line[2], path);
		command_n(&line[2], envp);
		ft_free_stringtab(path);
		dup2(save_fd, STDIN_FILENO);
		close(fd);
		close(save_fd);
		return (1);
	}
	return (0);
}

void	execute_command(char **line, t_list *envp)
{
	char	**path;

	path = init_path(envp);
	if (!path)
		return ;
	if (check_command(line, path, envp))
		return ;
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path);
	if (!line[0])
		return ;
	command_n(line, envp);
	ft_free_stringtab(path);
}

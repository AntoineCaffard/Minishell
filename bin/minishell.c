/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:12:21 by trebours          #+#    #+#             */
/*   Updated: 2024/02/22 16:29:08 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_chr_link(char *src, char **path)
{
	char	*verif_link;
	char	*save;
	int		i;

	i = 0;
	while (path[i])
	{
		save = ft_strjoin("/", src);
		verif_link = ft_strjoin(path[i], save);
		if (access(verif_link, X_OK) == 0)
		{
			free(src);
			free(save);
			return (verif_link);
		}
		i++;
		free(save);
		free(verif_link);
	}
	dup2(2, 1);
	ft_printf("minishell: %s: command not found\n", src);
	return (NULL);
}

char	*ft_chr_path(char **envp)
{
	int	i;
	char	*chr;

	i = 0;
	chr = "PATH\0";
	while (envp[i])
	{
		if (ft_strnstr(envp[i], chr, 4))
			return	(envp[i]);
		i++;
	}
	return (NULL);
}

void	command_n(char **cmd, char **envp)
{
	pid_t	tfork;

	tfork = fork();
	if (tfork < 0)
		return ;
	if (tfork == 0)
	{
		// printf("%s\n", cmd[0]);
		if (execve(cmd[0], cmd, envp))
		{
			ft_free_stringtab(cmd);
			return ;
		}
	}
	else
	{
		wait(NULL);
		ft_free_stringtab(cmd);
	}
}

void	ft_cmd(char **line, char **envp)
{
	char *path;
	char **path_split;

	path = ft_chr_path(envp);
	if (!path)
		return ;
	path_split = ft_split_str(path, ":");
	if (!path_split)
		return ; 
	if (access(line[0], X_OK))
		line[0] = ft_chr_link(line[0], path_split);
	// printf("%s\n", line[0]);
	command_n(line, envp);
	// ft_free_stringtab(line);
	ft_free_stringtab(path_split);
}

void	minishell(char **envp)
{
	// char	*line;
	char	**line_split;	

	// while (1)
	// {
		/* line = readline(">"); */
		line_split = ft_split_str("ls", " ");
		ft_cmd(line_split, envp);
	// }
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	minishell(envp);
	return (0);
}
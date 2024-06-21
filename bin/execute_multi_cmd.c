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
	// close(pipe_fds->std_fd[0]);
	// close(pipe_fds->std_fd[1]);
	// int i = open("/home/utilisateur/Bureau/Minishell/test", O_APPEND | O_RDONLY);
	// write(2, cmd[0], ft_strlen(cmd[0]));
	// write(2, "\n123\n", 6);
	// write(2, cmd[1], ft_strlen(cmd[1]));
	// write(2, "\n", 2);
	if (execve(cmd[0], cmd, NULL /*envp*/))
	{
		ft_free_stringtab(envp);
		perror("execve");
		exit (1);
	}
	return (1);
}

int	execute_multi(char **line, t_list *t_envp, t_pipe *pipe_fds)
{
	char	**path;
	char	**envp;
	int		error;

	path = init_path(t_envp);
	if (access(line[0], X_OK))
		line[0] = init_link(line[0], path);
	if (!line[0])
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

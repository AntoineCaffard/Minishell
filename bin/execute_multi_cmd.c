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
	int		error;

	error = 0;
	(void)pipe_fds;
	// close(pipe_fds->std_fd[0]);
	// close(pipe_fds->std_fd[1]);
	if (execve(cmd[0], cmd, envp))
	{
		ft_free_stringtab(envp);
		perror("execve");
		exit (1);
	}
	return (error);
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
	write(2, "ddddddddddd\n", 12);
	ft_free_stringtab(path);
	return (error);
}

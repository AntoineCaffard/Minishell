/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:11:17 by trebours          #+#    #+#             */
/*   Updated: 2024/07/24 05:19:20 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_error(int *error)
{
	if (*error == 127 || *error == 126)
		return ;
	else if (WIFEXITED(*error))
		*error = WEXITSTATUS(*error);
	else if (WIFSIGNALED(*error))
		*error = WTERMSIG(*error) + 128;
}

static int	single_parent(char **envp, t_pipe *fds, pid_t pid)
{
	int	error;

	ft_free_stringtab(envp);
	dup2(fds->std_fd[0], STDIN_FILENO);
	dup2(fds->std_fd[1], STDOUT_FILENO);
	while (waitpid(pid, &error, 0) != -1)
		continue ;
	if (WIFSIGNALED(error))
		return (WTERMSIG(error) + 128);
	return (WEXITSTATUS(error));
}

static int	command_n(char **cmd, char **envp, t_pipe *pipe_fds)
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
		return (single_parent(envp, pipe_fds, tfork));
	return (error);
}

int	verif_stat(char **line, char **path)
{
	struct stat	buf;

	if (stat(line[0], &buf))
	{
		write(2, "No such file or directory\n", 26);
		ft_free_stringtab(path);
		return (127);
	}
	if (S_ISDIR(buf.st_mode))
	{
		write(2, "Is a directory\n", 15);
		ft_free_stringtab(path);
		return (126);
	}
	if (access(line[0], X_OK))
	{
		write(2, "Permission denied\n", 18);
		ft_free_stringtab(path);
		return (126);
	}
	return (0);
}

int	execute_command(char **line, t_list *t_envp, t_pipe *pipe_fds)
{
	char		**path;
	char		**envp;
	int			error;

	error = 0;
	path = init_path(t_envp);
	if (ft_strchr(line[0], '/'))
	{
		error = verif_stat(line, path);
		if (error)
			return (error);
	}
	else
		line[0] = init_link(line[0], path, &error);
	if (!line[0] || error > 0)
	{
		if (path)
			ft_free_stringtab(path);
		return (error);
	}
	envp = tabify_list(t_envp);
	error = command_n(line, envp, pipe_fds);
	ft_free_stringtab(path);
	check_error(&error);
	return (error);
}

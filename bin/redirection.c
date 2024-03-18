/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:11:47 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 08:59:04 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redirect_save_fd(int save_fd[2], int action)
{
	if (action == 1)
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
	}
	else if (action == 2)
	{
		dup2(save_fd[0], STDIN_FILENO);
		dup2(save_fd[1], STDOUT_FILENO);
		close(save_fd[0]);
		close(save_fd[1]);
	}
}

static int	redirect_input(char **line, int save_fd[2])
{
	int fd;
	
	fd = open(line[1], O_RDONLY);
	if (fd == -1)
	{
		display_error("No such file or directory", line[1]);
		redirect_save_fd(save_fd, 2);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redirect_output(char **line, int save_fd[2])
{
	int fd;
	int	len;
	
	len = ft_stringtab_len(line);
	fd = open(line[len - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		display_error("file can not be creat", line[len - 1]);
		redirect_save_fd(save_fd, 2);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(line[len - 1]);
	line[len - 1] = NULL;
	free(line[len - 2]);
	line[len - 2] = NULL;
	return (0);
}

int	main_redirection(char **line, t_list *envp)
{
	int	i;
	int	len;
	int	save_fd[2];

	i = 0;
	len = ft_stringtab_len(line);
	redirect_save_fd(save_fd, 1);
	if (len >= 3 && !ft_strncmp(line[0], "<", ft_strlen(line[0])))
	{
		if (redirect_input(line, save_fd))
			return (1);
		else
			i = 2;
	}
	if (len >= 3 && !ft_strncmp(line[len - 2], ">", ft_strlen(line[len - 2])))
	{
		if (redirect_output(line, save_fd))
			return (0);
	}
	ft_start_minishell(&line[i], &envp);
	redirect_save_fd(save_fd, 2);
	return (0);
}

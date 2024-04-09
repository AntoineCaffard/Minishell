/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:23:05 by trebours          #+#    #+#             */
/*   Updated: 2024/03/27 09:01:30 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	output_utils(char **line, char *chr, int fd, int len)
{
	int	pos;
	int	save;

	pos = 0;
	save = 0;
	while (pos != -1)
	{
		pos = locate_string_in_stringtab(&line[save], chr, len);
		if (pos == -1)
			break ;
		if (fd > 2)
			close (fd);
		if (line[save + pos][len] == '\0')
			fd = open(line[save + pos + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(&line[save + pos][2], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (line[save + pos][len] != '\0')
			save += 1;
		else
			save += pos + 1;
	}
	return (fd);
}

static int	output_append(char **line)
{
	int	fd;

	fd = -5;
	fd = output_utils(line, ">>", fd, 2);
	if (fd == -5)
		return (1);
	if (fd == -1)
	{
		display_error("Error occurred when opening the file", "OUTPUT_APPEND");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	isolate_cmd(char **line)
{
	int	i;
	int	pos_out;

	i = 0;
	pos_out = 0;
	while (!pos_out)
	{
		pos_out = locate_string_in_stringtab(&line[i], ">>", 2);
		if (pos_out)
			break;
		if (pos_out != -1 && line[pos_out][2] != '\0')
			i++;
		else
			i += 2;
	}
	if (pos_out > 0)
		loop_isolate_cmd(line, pos_out, i);
	return (i);
}

int	main_append(char **line, t_list *envp)
{
	int	i;
	int	save_fd[2];

	redirect_save_fd(save_fd, 1);
	if (ft_parsing_output(line, ">>", 2) > 0)
	{
		redirect_save_fd(save_fd, 2);
		return (1);
	}
	if (output_append(line))
	{
		redirect_save_fd(save_fd, 2);
		return (1);
	}
	i = isolate_cmd(line);
	if (line[i])
		ft_start_minishell(&line[i], &envp);
	redirect_save_fd(save_fd, 2);
	return (0);
}

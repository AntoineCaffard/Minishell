/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:23:05 by trebours          #+#    #+#             */
/*   Updated: 2024/03/22 13:46:00 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parsing_output(char **line, char *chr, int len)
{
	int	save;
	int	position;

	save = 0;
	position = 0;
	while (position != -1)
	{
		position = locate_string_in_stringtab(&line[save], chr, len);
		if (position == -1)
			return (-1);
		if (line[save + position][len] == '\0'
			&& line[save + position + 1] == NULL)
		{
			display_error("syntax error unexpected token `newline\'", NULL);
			return (1);
		}
		if (line[position][len] != '\0')
			save += 1;
		if (position > 0)
			save += position + 1;
		else
			save += 2;
	}
	return (0);
}

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
			fd = open(line[save + pos + 1],
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(&line[save + pos][2],
					O_CREAT | O_APPEND | O_WRONLY, 0644);
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
			break ;
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

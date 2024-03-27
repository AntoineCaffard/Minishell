/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:31:39 by trebours          #+#    #+#             */
/*   Updated: 2024/03/27 09:02:01 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	input_utils(char **line, char *chr)
{
	int	pos;
	int	len;
	int	save;

	pos = 0;
	len = ft_strlen(chr);
	save = 0;
	if (locate_string_in_stringtab(&line[save], chr, len) == -1)
		return (-1);
	while (pos != -1)
	{
		if (ft_parsing(&line[save]))
			return (-1);
		pos = locate_string_in_stringtab(&line[save], chr, len);
		if (pos == -1)
			break ;
		if (line[pos][len] != '\0')
			save += 1;
		else
			save += pos + 1;
	}
	if (save != 0)
		return (save - 1);
	return (save);
}

int	redirect_input(char **line)
{
	int	fd;
	int	position;

	position = input_utils(line, "<");
	fd = -1;
	if (position == -1)
		return (-1);
	if (line[position][1] == '\0')
		fd = open(line[position + 1], O_RDONLY);
	else if (position != -1)
		fd = open(&line[position][1],O_RDONLY);
	if (fd == -1)
	{
		display_error("Error occurred when opening the file", "INPUT");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
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
		if (line[save   + pos][len] == '\0')
			fd = open(line[save + pos + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(&line[save + pos][1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (line[pos][len] != '\0')
			save += 1;
		else if (pos > 0)
			save += pos + 1;
		else
			save += 2;
	}
	return (fd);
}

int	redirect_output(char **line)
{
	int	fd;

	fd = -5;
	fd = output_utils(line, ">", fd, 1);
	if (fd == -5)
		return (1);
	if (fd == -1)
	{
		display_error("Error occurred when opening the file", "OUTPUT");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

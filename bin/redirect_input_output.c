/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:31:39 by trebours          #+#    #+#             */
/*   Updated: 2024/03/20 13:40:06 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_parsing(char **line)
{
	int	position_input;
	int	position_output;
	int	len;
	
	len = ft_stringtab_len(line);
	position_input = locate_string_in_stringtab(line, "<", 1);
	position_output = locate_string_in_stringtab(line, ">", 1);
	if (position_input == -1 && position_output == -1)
		return (0);
	if ((position_input != -1 && line[position_input][1] == '\0' && len < 2)
		|| (position_output != -1 && !line[position_output][1] && len < 2))
	{
		display_error("syntax error near unexpected token `newline\'", NULL);
		return (1);
	}
	if ((position_input != -1 && line[position_input][1] != '\0'
		&& access(&line[position_input][1], R_OK) == -1)|| (position_input != -1 
		&& line[position_input][1] == '\0'
		&& access(line[position_input + 1], R_OK) == -1))
	{
		display_error("No such file or directory", line[position_input + 1]);
		return (1);
	}
	return (0);
}

static int	input_utils(char **line, char *chr)
{
	int	pos;
	int	len;
	int	save;

	pos = 0;
	len = ft_strlen(chr);
	save = 0;
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
		return (0);
	if (line[position][1] == '\0')
		fd = open(line[position + 1], O_RDONLY);
	else if (position != -1)
		fd = open(&line[position][1],O_RDONLY);
	if (fd == -1)
	{
		display_error("Error occurred when opening the file", line[1]);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_output(char **line)
{
		int	fd;
	int	position;

	position = input_utils(line, ">");
	fd = -1;
	if (position == -1)
		return (0);
	if (line[position][1] == '\0')
		fd = open(line[position + 1], O_CREAT | O_TRUNC | O_RDONLY, 0644);
	else if (position != -1)
		fd = open(&line[position][1], O_CREAT | O_TRUNC | O_RDONLY, 0644);
	if (fd == -1)
	{
		display_error("Error occurred when opening the file", line[1]);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

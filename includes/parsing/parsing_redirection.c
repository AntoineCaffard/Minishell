/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:00:48 by trebours          #+#    #+#             */
/*   Updated: 2024/03/27 09:22:38 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

static int	_verif(char **line, int pos, int len)
{
	if (line[pos][len] == '\0' && (line[pos + 1] == NULL))
	{
		error_redirection("Newline");
		return (1);
	}
	if ((line[pos][len] == '\0' && line[pos + 1][0] == '>')
		|| line[pos][len] == '>')
	{
		error_redirection(">");
		return (1);
	}
	if ((line[pos][len] == '\0' && line[pos + 1][0] == '<')
		|| line[pos][len] == '<')
	{
		error_redirection("<");
		return (1);
	}
	return (0);
}

int	ft_parsing_output(char **line, char *chr, int len)
{
	int save;
	int	pos;

	save = 0;
	pos = 0;
	while (pos != -1)
	{
		pos = locate_string_in_stringtab(&line[save], chr, len);
		if (pos == -1)
			return (-1);
		if (_verif(line, save + pos, len))
			return (1);
		if (line[pos][len] != '\0')
			save += 1;
		if (pos > 0)
			save += pos + 1;
		else
			save += 2;
	}
	return (0);
}

int	ft_parsing(char **line)
{
	int	pos;
	int	len;
	
	len = ft_stringtab_len(line);
	pos = locate_string_in_stringtab(line, "<", 1);
	if (pos == -1)
		return (0);
	if (_verif(line, pos, 1))
		return (1);
	if ((pos != -1 && line[pos][1] != '\0'
		&& access(&line[pos][1], R_OK) == -1)|| (pos != -1
		&& line[pos][1] == '\0' && access(line[pos + 1], R_OK) == -1))
	{
		display_error("No such file or directory", line[pos + 1]);
		return (1);
	}
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:05:13 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/22 11:24:26 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_double_pipe(char *string)
{
	int	res;

	res = 0;
	while (string[res])
	{
		if (string[res] == '|')
		{
			if (string[res + 1] == '|')
				return (res);
		}
		res++;
	}
	return (-1);
}

int	lexer(char *string)
{
	int	res;

	res = skip_spaces(string);
	if (string[res] == '|')
		return (res);
	res = ft_strlen(string) - 1;
	while (res >= 0 && is_space(string[res]))
		res--;
	if (string[res] == '|')
		return (res);
	res = check_double_pipe(string);
	if (res != -1)
		return (res);
	return (0);
}

int	skip_quotes(char *line, int i)
{
	int	j;

	j = 1;
	while (line[i + j] && line [i + j] != line[i])
		j++;
	return (j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:51:18 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/26 09:43:02 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_double_pipe(char *string)
{
	int	res;

	res = 0;
	while (string[res])
	{
		if (string[res] == '\'' || string[res] == '\"')
			res += skip_quotes(string, res) - 1;
		else if (string[res] == '|')
		{
			res++;
			res += skip_spaces(&string[res]);
			if (string[res] == '|')
				return (res);
		}
		res++;
	}
	return (-1);
}

static int	check_redirs(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '<' || string[i] == '>')
		{
			i++;
			if (string[i] == string[i -1])
				i++;
			while (string[i] && is_space(string[i]))
				i++;
			if (string[i] == '<' || string[i] == '>' || string[i] == '|')
				return (i);
		}
		else
			i++;
	}
	return (-1);
}

int	lexer(char *string)
{
	int	res;
	int	tmp;

	res = skip_spaces(string);
	if (string[res] == '|' || !string[res])
		return (res);
	res = 0;
	tmp = check_double_pipe(string);
	if (tmp != -1)
		res = tmp;
	tmp = check_redirs(string);
	if (tmp != -1 && (tmp < res || res == 0))
		res = tmp;
	tmp = ft_strlen(string) - 1;
	while (tmp >= 0 && is_space(string[tmp]))
		tmp--;
	if (string[tmp] == '|' && (tmp < res || res == 0))
		res = tmp;
	return (res);
}

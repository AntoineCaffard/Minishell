/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:51:18 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:51:18 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
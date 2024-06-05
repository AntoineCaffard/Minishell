/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:47:37 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/04 15:28:52 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_space(char c)
{
	if (c == ' ')
		return (TRUE);
	if (c >= 9 && c <= 13)
		return (TRUE);
	return (FALSE);
}

bool	minishell_is_separator(char c)
{
	if (is_space(c))
		return (TRUE);
	if (c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

bool	is_redir(t_argument *arg)
{
	if (arg->value[0] == '<' || arg->value[0] == '>')
		return (TRUE);
	return (FALSE);
}

int	skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}

t_redirection_type	get_type(t_argument *arg)
{
	char	*str;

	str = arg->value;
	if (str[0] == '<')
	{
		if (!str[1])
			return (REDIRECTION_INFILE);
		return (REDIRECTION_HEREDOC);
	}
	if (!str[1])
		return (REDIRECTION_OUTFILE);
	return (REDIRECTION_APPEND);
}

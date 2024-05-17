/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:47:37 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/17 10:31:55 by Trebours         ###   ########.fr       */
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
	if (c == '<' || c == '>' || c == '$')
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

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	len;
	char	*str;
	char	*res;

	i = 0;
	len = 0;
	str = (char *) s;
	while (str[len] && len < n)
		len++;
	res = (char *) malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
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

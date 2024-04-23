/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:47:37 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/23 13:33:13 by acaffard         ###   ########.fr       */
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

bool	is_separator(char c)
{
	if (is_space(c))
		return (TRUE);
	if (c == '<' || c == '>' || c == '$')
		return (TRUE);
	return (FALSE);
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

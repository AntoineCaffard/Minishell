/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:26:25 by trebours          #+#    #+#             */
/*   Updated: 2024/05/30 11:26:27 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_quote(char *args)
{
	int	j;

	if (!args)
		return (0);
	j = 0;
	while (args[j])
	{
		if (args[j] == '\"' || args[j] == '\'')
			return (args[j]);
		j++;
	}
	return (0);
}

int	ft_charchr(const char *s, unsigned int y)
{
	char	*str;
	int		i;

	if (!s)
		return (-1);
	str = (char *) s;
	i = y;
	while (str[i])
	{
		if (str[i] == '\"' % 256 || str[i] == '\'' % 256)
			return (i);
		i++;
	}
	if (str[i] == '\"' % 256 || str[i] == '\'' % 256)
		return (i);
	return (-1);
}

int	ft_charrchr(const char *s, unsigned int y)
{
	char	*str;
	char	c;
	int		i;

	if (!s)
		return (-1);
	str = (char *) s;
	i = ft_charchr(s, y);
	if (i == -1)
		return (-1);
	c = s[i];
	i++;
	while (str[i])
	{
		if (str[i] == c % 256)
			return (i);
		i++;
	}
	if (str[i] == c % 256)
		return (i);
	return (-1);
}

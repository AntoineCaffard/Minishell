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

int	verif_quote(char *args, char c)
{
	int	j;

	j = 0;
	while (args[j])
	{
		if (!c && (args[j] == '\"' || args[j] == '\''))
			return (args[j]);
		else if (c && args[j] == c)
			return (args[j]);
		j++;
	}
	return (0);
}

int	ft_charchr(const char *s)
{
	char	*str;
	int		i;

	str = (char *) s;
	i = 0;
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

int	ft_charrchr(const char *s)
{
	char	*str;
	char	c;
	int		i;

	str = (char *) s;
	i = ft_charchr(s);
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

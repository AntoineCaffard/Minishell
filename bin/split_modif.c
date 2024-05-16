/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:56:25 by trebours          #+#    #+#             */
/*   Updated: 2024/02/28 10:00:35 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_word(char *src)
{
	int	nmb_word;
	int	i;
	int	h;

	i = 0;
	h = 0;
	nmb_word = 0;
	if (!src[i])
		return (0);
	if (src[i] == ' ')
		i++;
	if (src[ft_strlen(src) - 1] != ' ')
		nmb_word = 1;
	while (src[i])
	{
		if (src[i] == '\"' && h == 0)
			h = 1;
		else if (src[i] == '\"' && h == 1)
			h = 0;
		if (src[i] == ' ' && src[i - 1] != ' ' && h == 0)
			nmb_word++;
		i++;
	}
	return (nmb_word);
}

static size_t	ft_lenword(const char *s, char chr)
{
	size_t	i;

	i = 0;
	while (s[i] != chr && s[i])
		i++;
	return (i);
}

static char	*ft_strdup_mod(const char *s, char chr)
{
	char	*rsl;
	size_t	len_s;
	int		i;

	i = 0;
	len_s = ft_lenword(s, chr);
	rsl = (char *)ft_calloc((len_s + 1), sizeof(char));
	if (rsl == 0)
		return (0);
	while (s[i] && s[i] != chr)
	{
		rsl[i] = s[i];
		i++;
	}
	return (rsl);
}

static void	ft_loop_split(char *src, char c, char ***rsl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		while (src[i] && src[i] == c)
			i++;
		if (src[i] == '\"' && c == ' ')
			c = '\"';
		if (src[i] && src[i] != c)
		{
			rsl[0][j++] = ft_strdup_mod(&src[i], c);
			while (src[i] && src[i] != c)
				i++;
			c = ' ';
			if (src[i] && src[i] != c)
				i++;
		}
	}
}

char	**ft_split_modif(char *src, char c)
{
	char	**rsl;

	if (!src)
		return (0);
	rsl = ft_calloc(ft_count_word(src) + 1, sizeof(char *));
	if (!rsl)
		return (0);
	ft_loop_split(src, c, &rsl);
	return (rsl);
}

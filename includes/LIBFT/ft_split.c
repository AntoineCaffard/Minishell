/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:02:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 09:37:55 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char const *word, size_t st, char c)
{
	size_t	i;

	i = 0;
	while ((word)[st + i] != '\0' && ((char *)word)[st + i] != c)
		i++;
	return (i);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	res;

	i = 1;
	res = 0;
	if (!s[0])
		return (0);
	if (s[0] != c)
		res++;
	while (s[i])
	{
		if (s[i] != c && s[i -1] == c && s[i])
			res++;
		i++;
	}
	return (res);
}

static void	fill(char const *s, char c, char **res)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	if (((char *)s)[0] != c)
	{
		res[j] = ft_substr(s, 0, word_len(s, 0, c));
		j++;
	}
	while (((char *)s)[i])
	{
		if (((char *)s)[i] != c && ((char *)s)[i -1] == c)
		{
			res[j] = ft_substr(s, i, word_len(s, i, c));
			j++;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (size == 0)
		return (res);
	fill(s, c, res);
	i = 0;
	while (res[i])
		i++;
	if (i != size)
	{
		ft_free_stringtab(res);
		return (NULL);
	}
	return (res);
}

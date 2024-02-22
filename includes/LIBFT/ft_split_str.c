/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:46:31 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 10:18:52 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_separator(char *separator, int c)
{
	if (!separator)
		return (0);
	while (*separator)
	{
		if (c == *separator)
			return (42);
		separator++;
	}
	return (0);
}

static size_t	word_len(char const *word, size_t st, char *separator)
{
	size_t	i;

	i = 0;
	while ((word)[st + i] != '\0' &&
	!is_separator(separator, ((char *)word)[st + i]))
		i++;
	return (i);
}

static size_t	count_words(char const *s, char *separator)
{
	size_t	i;
	size_t	res;

	i = 1;
	res = 0;
	if (!s[0])
		return (0);
	if (!is_separator(separator, s[0]))
		res++;
	while (s[i])
	{
		if (!is_separator(separator, s[i]) && \
			is_separator(separator, s[i -1]) && s[i])
			res++;
		i++;
	}
	return (res);
}

static void	fill(char const *s, char *separator, char **res)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	if (!is_separator(separator, ((char *)s)[0]))
	{
		res[j] = ft_substr(s, 0, word_len(s, 0, separator));
		j++;
	}
	while (((char *)s)[i])
	{
		if (!is_separator(separator, ((char *)s)[i]) &&
		is_separator(separator, ((char *)s)[i -1]))
		{
			res[j] = ft_substr(s, i, word_len(s, i, separator));
			j++;
		}
		i++;
	}
}

char	**ft_split_str(char const *s, char *separator)
{
	char	**res;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	size = count_words(s, separator);
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (size == 0)
		return (res);
	fill(s, separator, res);
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

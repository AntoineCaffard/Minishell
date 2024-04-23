/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:24:16 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:01:07 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	res = ft_calloc((get_len(s + start, len) + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (((char *)s)[i + start] && i < len)
	{
		res[i] = ((char *)s)[i + start];
		i++;
	}
	return (res);
}

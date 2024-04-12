/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:46:08 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 08:42:43 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = 0;
	while (((char *)s1)[start] && char_in_set(((char *)s1)[start], set))
		start++;
	if (((char *)s1)[start] == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (((char *)s1)[end] && char_in_set(((char *)s1)[end], set))
		end --;
	return (ft_substr(s1, start, end - start + 1));
}

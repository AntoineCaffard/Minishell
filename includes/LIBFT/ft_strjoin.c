/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:51:19 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/06 09:25:48 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_length;
	size_t	i;
	size_t	j;
	char	*res;	

	if (!s1 || !s2)
		return (NULL);
	total_length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *) ft_calloc(total_length + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && ((char *)s1)[i])
	{
		res[i] = ((char *)s1)[i];
		i++;
	}
	j = 0;
	while (s2 && ((char *)s2)[j])
	{
		res[i + j] = ((char *)s2)[j];
		j++;
	}
	return (res);
}

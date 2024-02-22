/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:21:21 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:07:00 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*str;
	char	*res;

	i = 0;
	len = 0;
	str = (char *) s;
	while (str[len])
		len++;
	res = (char *) malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (*str)
	{
		res[i] = *str;
		i++;
		str++;
	}
	res[i] = '\0';
	return (res);
}

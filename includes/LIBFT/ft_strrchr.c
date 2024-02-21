/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:10:49 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:05:15 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*res;

	str = (char *) s;
	res = NULL;
	while (*str)
	{
		if (*str == c % 256)
			res = str;
		str++;
	}
	if (*str == c % 256)
		return (str);
	return (res);
}

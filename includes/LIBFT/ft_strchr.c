/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:59:59 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:07:19 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *) s;
	while (*str)
	{
		if (*str == c % 256)
			return (str);
		str++;
	}
	if (*str == c % 256)
		return (str);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:20:42 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/09 10:06:32 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (size == 0 && (!dst || !src))
		return (0);
	len = ft_strlen(dst);
	if (size <= len)
		return (size + ft_strlen((char *) src));
	return (len + ft_strlcpy(dst + len, src, size - len));
}

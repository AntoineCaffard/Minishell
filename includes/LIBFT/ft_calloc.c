/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:16:23 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:12:09 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*result;
	size_t			i;

	if ((int) nmemb < 0 && (int) size < 0)
		return (NULL);
	if ((unsigned long long) nmemb * size > UINT_MAX)
		return (NULL);
	result = (unsigned char *) malloc(nmemb * size);
	if (!result)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

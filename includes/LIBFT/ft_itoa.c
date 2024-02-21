/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:44:26 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 09:45:54 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_n_len(int n)
{
	size_t	count;

	count = 0;
	if (n < 0)
		count ++;
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	count;

	if (n == 0)
		return (ft_strdup("0"));
	count = get_n_len(n);
	res = (char *) ft_calloc(count + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		res[count - 1] = (n % -10) * -1 + '0';
		n = n / -10;
		count --;
	}
	while (n != 0)
	{
		res[count - 1] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (res);
}

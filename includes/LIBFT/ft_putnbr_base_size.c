/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:27:01 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:17:39 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_size(long long n, char	*base, int size)
{
	int	res;

	res = 0;
	if (n < 0)
	{
		res += ft_putchar_size('-');
		if (n / size != 0)
			res += ft_putnbr_base_size(n / (size * -1), base, size);
		res += ft_putchar_size(base[(n % (size * -1)) * -1]);
		return (res);
	}
	if (n > size - 1)
		res += ft_putnbr_base_size(n / size, base, size);
	res += ft_putchar_size(base[(n % size)]);
	return (res);
}

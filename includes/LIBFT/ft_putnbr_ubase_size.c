/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ubase_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:28:18 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:06:45 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ubase_size(unsigned long long n, char	*base, unsigned int s)
{
	int	res;

	res = 0;
	if (n > (s - 1))
		res += ft_putnbr_ubase_size(n / s, base, s);
	res += ft_putchar_size(base[(n % s)]);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:05:28 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:17:46 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hexa(unsigned long long n, char c)
{
	if (c == 'p')
	{
		ft_putstr_size("0x");
		return (2 + ft_putnbr_ubase_size(n, "0123456789abcdef", 16));
	}
	if (c == 'X')
		return (ft_putnbr_ubase_size(n, "0123456789ABCDEF", 16));
	return (ft_putnbr_ubase_size(n, "0123456789abcdef", 16));
}

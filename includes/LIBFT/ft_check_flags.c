/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:01:05 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:07:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_word(va_list a, const char c)
{
	int	res;

	res = -1;
	if (c == 'c')
		res = ft_putchar_size(va_arg(a, int));
	if (c == 's')
		res = ft_putstr_size(va_arg(a, char *));
	if (c == '%')
		res = ft_putchar_size('%');
	return (res);
}

static int	is_hexa(va_list a, const char c)
{
	unsigned long	p;
	int				res;

	res = -1;
	if (c == 'p')
	{
		p = va_arg(a, unsigned long);
		if (p)
			res = ft_print_hexa(p, c);
		else
			res = ft_putstr_size("(nil)");
	}
	if (c == 'x' || c == 'X')
		res = ft_print_hexa(va_arg(a, unsigned int), c);
	return (res);
}

static int	is_nbr(va_list a, const char c)
{
	int	res;

	res = -1;
	if (c == 'd' || c == 'i')
		res = ft_putnbr_base_size(va_arg(a, int), "0123456789", 10);
	if (c == 'u')
		res = ft_putnbr_base_size(va_arg(a, unsigned int), "0123456789", 10);
	return (res);
}

int	ft_check_flags(va_list a, const char c)
{
	int	result;

	result = is_word(a, c);
	if (result == -1)
		result = is_hexa(a, c);
	if (result == -1)
		result = is_nbr(a, c);
	return (result);
}

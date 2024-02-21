/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:31:57 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:06:20 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	int		total_length;
	int		i;

	total_length = 0;
	i = 0;
	va_start(lst, s);
	while (s[i])
	{
		if (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]) != 0)
		{
			total_length += ft_check_flags(lst, s[i + 1]);
			i++;
		}
		else
			total_length += ft_putchar_size(s[i]);
		i++;
	}
	va_end(lst);
	return (total_length);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:25:29 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:08:02 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_size(char *s)
{
	int	res;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	res = 0;
	while (*s)
	{
		res += ft_putchar_size(*s);
		s++;
	}
	return (res);
}

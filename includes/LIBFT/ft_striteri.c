/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:27:59 by acaffard          #+#    #+#             */
/*   Updated: 2023/11/08 10:37:17 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))

{
	size_t	i;

	i = 0;
	if (!f || !s)
		return ;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

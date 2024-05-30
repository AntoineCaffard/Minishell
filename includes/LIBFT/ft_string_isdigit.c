/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_isdigit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:09:41 by trebours          #+#    #+#             */
/*   Updated: 2024/05/30 09:09:36 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_string_isdigit(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (ft_isdigit(src[i]) || (i == 0 && (src[0] == '+' || src[0] == '-')))
			i++;
		else
			return (0);
	}
	return (1);
}

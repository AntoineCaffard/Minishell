/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_isdigit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:09:41 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 09:28:29 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_string_isdigit(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (ft_isdigit(src[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

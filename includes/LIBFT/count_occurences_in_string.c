/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_occurences_in_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:31:32 by trebours          #+#    #+#             */
/*   Updated: 2024/02/22 10:32:29 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_occurences_in_string(const char *src, const char c)
{
	int	i;
	int	count;

	if (!src)
		return (0);
	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == c)
			count++;
		i++;
	}
	return (count);
}

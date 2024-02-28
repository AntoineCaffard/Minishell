/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:37:22 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/28 10:49:01 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_lst_get_index(t_list *list, t_list *node)
{
	size_t	res;
	if(!list | !node)
		return (-1);
	res = 0;
	while (list)
	{
		if (list == node)
			return (res);
		res++;
		list = list->next;
	}
	return (-1);
}

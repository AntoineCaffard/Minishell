/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_lstget_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:07:32 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 11:07:48 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_int_list.h"

size_t	ft_int_lstget_index(t_int_list *list, t_int_list *node)
{
	size_t	res;

	if (!list | !node)
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

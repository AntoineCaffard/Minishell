/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_lstpop_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:17:02 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 12:19:44 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_int_list.h"

void	ft_int_lstpop_index(t_int_list **list, int index)
{
	t_int_list	*tmp;

	if (!list || !*list || index >= ft_int_lstsize(*list))
		return ;
	if (index == 0)
	{
		tmp = *list;
		*list = tmp->next;
		free(tmp);
		return ;
	}
	ft_int_lstpop_index(&((*list)->next), index - 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:13:09 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/26 13:37:06 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_remove_index(t_list **list, int index)
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	if (index >= ft_lstsize(*list))
		return ;
	if (index == 0)
	{
		tmp = *list;
		*list = tmp->next;
		return ;
	}
	ft_lst_remove_index(&((*list)->next), index - 1);
}

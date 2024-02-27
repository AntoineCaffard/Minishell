/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:13:09 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/27 10:11:03 by acaffard         ###   ########.fr       */
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
		ft_lstdelone(tmp, free);
		return ;
	}
	ft_lst_remove_index(&((*list)->next), index - 1);
}

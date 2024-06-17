/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_lstclear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:21:43 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 12:22:06 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_int_list.h"

void	ft_int_lstclear(t_int_list **lst)
{
	if (!lst || !(*lst))
		return ;
	if (((*lst)->next) != NULL)
		ft_int_lstclear(&((*lst)->next));
	free(lst);
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:19:25 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 09:20:58 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_redlist.h"

void	ft_redclear(t_redlist **list, void (*del)(void*))
{
	if (!list || !del || !*list)
		return ;
	if (((*list)->next) != NULL)
		ft_clear_list(&(*list)->next, del);
	ft_red_delone(list, del);
}

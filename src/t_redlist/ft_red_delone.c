/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:17:30 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 09:18:32 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_redlist.h"

void	ft_red_delone(t_redlist **list, void (*del)(void*))
{
	if (!list || !del || !*list)
		return ;
	del((*list)->link);
	free(*list);
}

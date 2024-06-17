/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:47:03 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 15:49:44 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_arglist.h"

void	ft_argpush(t_arglist **list, t_arglist *to_push)
{
	if (!list || !to_push)
		return ;
	if (!*list)
		*list = to_push;
	else
		ft_arglast(*list)->next = to_push;
}

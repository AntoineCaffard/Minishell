/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:07:13 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 09:22:42 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_redlist.h"

void	ft_redpush(t_redlist **lst, t_redlist *to_push)
{
	if (!lst || !to_push)
		return ;
	if (!*lst)
	{
		*lst = to_push;
		return ;
	}
	t_redlast(*lst)->next = to_push;
}

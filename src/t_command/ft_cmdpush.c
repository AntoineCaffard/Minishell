/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:03:51 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 15:59:12 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_cmdlist.h"

void	ft_cmdpush(t_cmdlist **lst, t_cmdlist *to_push)
{
	if (!lst || !to_push)
		return ;
	if (!*lst)
	{
		*lst = to_push;
		return ;
	}
	ft_cmdlast(*lst)->next = to_push;
}

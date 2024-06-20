/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:24:14 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 09:28:06 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_cmdlist.h"

void	ft_cmd_delone(t_cmdlist **list, void (*del)(void*))
{
	if (!list || !del || !*list)
		return ;
	ft_argclear(&((*list)->args), free);
	ft_redclear(&((*list)->redirs), free);
	free(*list);
}

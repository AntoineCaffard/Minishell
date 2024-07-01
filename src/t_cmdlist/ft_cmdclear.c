/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:28:23 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 11:31:24 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_cmdlist.h"

void	ft_cmdclear(t_cmdlist **list, void (*del)(void*))
{
	if (!list || !del || !*list)
		return ;
	if (((*list)->next) != NULL)
		ft_cmdclear(&(*list)->next, del);
	ft_cmd_delone(list, del);
}

void	free_struct(t_cmdline	*line)
{
	t_cmdlist	*buffer;

	buffer = line->cmds;
	while (buffer)
	{
		line->cmds = buffer->next;
		ft_argclear(&buffer->args, free);
		ft_redclear(&(buffer->redirs), free);
		free(buffer);
		buffer = line->cmds;
	}
	free(buffer);
	line->cmds = NULL;
}

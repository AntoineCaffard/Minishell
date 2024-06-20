/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:35:12 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 15:59:07 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_cmdlist.h"

t_cmdlist	*ft_cmdnew(void)
{
	t_cmdlist	*new_command;

	new_command = ft_calloc(1, sizeof(t_cmdlist));
	if (!new_command)
		return (NULL);
	new_command->args = NULL;
	new_command->redirs = NULL;
	new_command->next = NULL;
	return (new_command);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:23:20 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/17 10:29:50 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*create_command(void)
{
	t_command	*res;

	res = ft_calloc(1, sizeof(t_command));
	if (!res)
		return (NULL);
	res->args = NULL;
	res->redirs = NULL;
	res->next = NULL;
	return (res);
}

t_command	*t_command_get_last(t_command *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (t_command_get_last(lst->next));
}

void	t_command_add_back(t_command **lst, t_command *new_tail)
{
	if (!lst || !new_tail)
		return ;
	if (!*lst)
	{
		*lst = new_tail;
		return ;
	}
	t_command_get_last(*lst)->next = new_tail;
}

t_command	*manage_creation(t_command_line *res)
{
	t_command	*command;

	command = create_command();
	if (!command)
		res->error_code = 1;
	t_command_add_back(&(res->commands), command);
	return (command);
}

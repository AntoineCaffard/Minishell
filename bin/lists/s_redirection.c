/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:04:21 by antoine           #+#    #+#             */
/*   Updated: 2024/04/15 11:10:59 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirection	*create_redirection(e_redirection_type type, char *link)
{
	t_redirection	*res;

	res = ft_calloc(1, sizeof(t_redirection));
	if (!res)
		return (NULL);
	res->type = type;
	res->link = link;
	res->next = NULL;
	return (res);
}

t_redirection	*t_redirection_get_last(t_redirection *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (t_redirection_get_last(lst->next));
}

void	t_redirection_add_back(t_redirection **lst, t_redirection *new_tail)
{
	if (!lst || !new_tail)
		return ;
	if (!*lst)
	{
		*lst = new_tail;
		return ;
	}
	t_redirection_get_last(*lst)->next = new_tail;
}

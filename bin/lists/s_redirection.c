/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:04:21 by antoine           #+#    #+#             */
/*   Updated: 2024/04/15 11:21:02 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*create_redir(e_redirection_type type, char *link)
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

t_redir	*t_redir_get_last(t_redir *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (t_redir_get_last(lst->next));
}

void	t_redir_add_back(t_redir **lst, t_redir *new_tail)
{
	if (!lst || !new_tail)
		return ;
	if (!*lst)
	{
		*lst = new_tail;
		return ;
	}
	t_redir_get_last(*lst)->next = new_tail;
}
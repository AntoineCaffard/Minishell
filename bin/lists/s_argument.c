/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_argument.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:01 by antoine           #+#    #+#             */
/*   Updated: 2024/04/15 11:11:36 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_argument	*create_argument(char *content)
{
	t_argument	*res;

	res = ft_calloc(1, sizeof(t_argument));
	if (!res)
		return (NULL);
	res->value = content;
	res->next = NULL;
	return (res);
}

t_argument	*t_argument_get_last(t_argument *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (t_argument_get_last(lst->next));
}

void	t_argument_add_back(t_argument **lst, t_argument *new_tail)
{
	if (!lst || !new_tail)
		return ;
	if (!*lst)
	{
		*lst = new_tail;
		return ;
	}
	t_argument_get_last(*lst)->next = new_tail;
}

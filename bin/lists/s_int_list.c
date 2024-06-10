/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_int_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:47:33 by trebours          #+#    #+#             */
/*   Updated: 2024/06/10 13:47:38 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_int_list	*ft_int_lstnew(int content)
{
	t_int_list	*res;

	res = ft_calloc(1, sizeof(t_int_list));
	if (!res)
		return (NULL);
	res->content = content;
	return (res);
}

t_int_list	*ft_int_lstlast(t_int_list *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (ft_int_lstlast(lst->next));
}

void	ft_int_lstadd_back(t_int_list **lst, t_int_list *new_tail)
{
	if (!lst || !new_tail)
		return ;
	if (!*lst)
	{
		*lst = new_tail;
		return ;
	}
	ft_int_lstlast(*lst)->next = new_tail;
}

size_t	ft_int_lst_get_index(t_int_list *list, t_int_list *node)
{
	size_t	res;

	if (!list | !node)
		return (-1);
	res = 0;
	while (list)
	{
		if (list == node)
			return (res);
		res++;
		list = list->next;
	}
	return (-1);
}

void	ft_int_lst_remove_index(t_int_list **list, int index)
{
	t_int_list	*tmp;

	if (!list || !*list)
		return ;
	if (index >= ft_int_lstsize(*list))
		return ;
	if (index == 0)
	{
		tmp = *list;
		*list = tmp->next;
		free(tmp);
		return ;
	}
	ft_int_lst_remove_index(&((*list)->next), index - 1);
}

int	ft_int_lstsize(t_int_list *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_int_lstsize(lst->next));
}

void	ft_int_lstclear(t_int_list **lst)
{
	if (!lst || !(*lst))
		return ;
	if (((*lst)->next) != NULL)
		ft_int_lstclear(&((*lst)->next));
	free(lst);
	*lst = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_argument.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:59:01 by antoine           #+#    #+#             */
/*   Updated: 2024/05/14 14:06:43 by acaffard         ###   ########.fr       */
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

t_argument	*remove_args_from_list(t_argument **args, t_argument *node)
{
	t_argument	*buffer;
	t_argument	*tmp;

	if (!args || !*args || !node)
		return NULL;
	if (*args == node)
	{
		buffer = *args;
		*args = (*args)->next->next;
		ft_delone_args(&(buffer->next), free);
		ft_delone_args(&buffer, free);

		return (*args);
	}
	else
	{
		buffer = *args;
		while (buffer->next && buffer->next != node)
			buffer = buffer->next;
		if (!buffer->next)
			return NULL;
		tmp = buffer->next;
		buffer->next = tmp->next->next;
		ft_delone_args(&(tmp->next), free);
		ft_delone_args(&tmp, free);
		return (buffer);
	}

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argpop_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:47:32 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 17:53:29 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_arglist.h"

static t_arglist	*change_head(t_arglist **head)
{
	t_arglist	*to_free;

	to_free = *head;
	*head = (*head)->next->next;
	ft_argdelone(&(to_free->next), free);
	ft_argdelone(&to_free, free);
	return (*head);
}

static t_arglist	*get_new_next(t_arglist *node)
{
	t_arglist	*new_next;

	new_next = node->next->next;
	ft_argdelone(&(node->next), free);
	ft_argdelone(&node, free);
	return (new_next);
}

t_arglist	*ft_argpop_two(t_arglist **head, t_arglist *node)
{
	t_arglist	*tmp;

	if (!head || !*head || !node)
		return (NULL);
	if (node == *head)
		return (change_head(head));
	tmp = *head;
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	tmp = get_new_next(tmp->next);
	return (tmp);
}

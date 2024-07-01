/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argpop_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:47:32 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 11:37:53 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_arglist.h"

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
	t_arglist	*buffer;
	t_arglist	*tmp;

	if (!head || !*head || !node)
		return (NULL);
	if (*head == node)
	{
		buffer = *head;
		*head = (*head)->next->next;
		get_new_next(buffer);
		return (*head);
	}
	else
	{
		buffer = *head;
		while (buffer->next && buffer->next != node)
			buffer = buffer->next;
		if (!buffer->next)
			return (NULL);
		tmp = buffer->next;
		buffer->next = tmp->next->next;
		get_new_next(tmp);
		return (buffer);
	}
}

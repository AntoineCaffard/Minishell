/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_new_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:08:27 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 13:27:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_add_new_node(t_list **list, char *value)
{
	t_list	*new_node;
	char	*value_copy;

	value_copy = ft_strdup(value);
	if (!value_copy)
		return (print_error(MALLOC_ERROR));
	new_node = ft_lstnew(value_copy);
	if (!new_node)
	{
		free(value_copy);
		return (print_error(MALLOC_ERROR));
	}
	ft_lstadd_back(list, new_node);
	return (0);
}

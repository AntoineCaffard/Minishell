/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sorted_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:12:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:33:22 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static t_list	*find_min(t_list *list)
{
	t_list	*res;

	res = list;
	while (list)
	{
		if (ft_strcmp(list->content, res->content) < 0)
			res = list;
		list = list->next;
	}
	return (res);
}

static void	print_sorted(t_list **list)
{
	t_list	*min;
	char	*content;
	int		min_index;
	size_t	e_index;

	while (ft_lstsize(*list) != 0)
	{
		min = find_min(*list);
		content = min->content;
		e_index = ft_env_var_len((char *) content);
		if (content[0] == '_' && content[1] == '=')
			;
		else if (!content[e_index])
			printf("declare -x %s\n", content);
		else
		{
			((char *)content)[e_index] = '\0';
			printf("declare -x %s=\"%s\"\n", content, &content[e_index + 1]);
		}
		min_index = ft_lst_get_index(*list, min);
		ft_lst_remove_index(list, min_index);
	}
}

static	t_list	*copy_list(t_list *to_copy)
{
	t_list	*new_list;
	int		error;

	new_list = NULL;
	while (to_copy)
	{
		error = ft_add_new_node(&new_list, (char *) to_copy->content);
		if (error == MALLOC_ERROR)
		{
			ft_lstclear(&new_list, free);
			return (NULL);
		}
		to_copy = to_copy->next;
	}
	return (new_list);
}

int	ft_print_sorted_env(t_list *list)
{
	t_list	*new_list;

	new_list = copy_list(list);
	if (!new_list)
		return (MALLOC_ERROR);
	print_sorted(&new_list);
	return (0);
}

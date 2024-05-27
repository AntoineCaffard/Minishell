/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/27 11:52:52 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"
#include "../LIBFT/libft.h"

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

static void	manage_print(t_list **list)
{
	t_list	*min;
	int		min_index;

	while (ft_lstsize(*list) != 0)
	{
		min = find_min(*list);
		printf("%s\n", (char *) min->content);
		min_index = ft_lst_get_index(*list, min);
		ft_lst_remove_index(list, min_index);
	}
}

int	print_sort_list(t_list *list)
{
	t_list	*res;
	t_list	*new;
	char	*new_string;

	res = NULL;
	while (list)
	{
		new_string = ft_strdup(list->content);
		if (!new_string)
		{
			ft_lstclear(&res, free);
			return (1);
		}
		new = ft_lstnew(new_string);
		if (!new)
		{
			ft_lstclear(&res, free);
			return (1);
		}
		ft_lstadd_back(&res, new);
		list = list->next;
	}
	manage_print(&res);
	return (0);
}

int	parsing_export(t_list **envp, char **params)
{
	int	error_code;

	error_code = 0;
	if (ft_stringtab_len(params) == 0)
		print_sort_list(*envp);
	else if (count_occurences_in_string(params[1], '=') > 1)
		return (1);
	else
		error_code = minishell_export(envp, params);
	return (error_code);
}

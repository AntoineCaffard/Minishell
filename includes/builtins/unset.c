/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:54:53 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 11:30:11 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*get_node_by_value(t_list *list, char *param)
{
	while (list)
	{
		if (ft_strncmp(((char *)(list->content)), param,
			ft_strlen(param)) == 0)
		{
			if (((char *)(list->content))[ft_strlen(param)] == '=')
				return (list);
		}
		list = list->next;
	}
	return (NULL);
}

void	minishell_unset(t_list **envp, char **params)
{
	int		i;
	int		index;
	t_list	*node;

	i = 0;
	while (params[i])
	{
		node = get_node_by_value(*envp, params[i]);
		if (node != NULL)
		{
			index = ft_lst_get_index(*envp, node);
			ft_lst_remove_index(envp, index);
		}
		i++;
	}
}

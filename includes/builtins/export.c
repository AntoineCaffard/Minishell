/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:55:40 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/27 14:26:13 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*get_node_by_value(t_list *list, char *param)
{
	while (list)
	{
		if (ft_strncmp(((char *) (list->content)), param, ft_strlen(param)) == 0)
		{
			if (((char *) (list->content))[ft_strlen(param)] == '=')
				return (list);
		}
		list = list->next;
	}
	return (NULL);
}

void	actualize_node_value(t_list *node, char *param)
{
		char	*tmp;

		tmp = ft_strdup(param);
		if (tmp)
		{
			free(node->content);
			node->content = tmp;
		}
}

void	add_new_env_var(t_list **envp, char *param)
{
	char	*tmp;
	t_list	*node;

	tmp = ft_strdup(param);
	if (!tmp)
		return ;
	node = ft_lstnew(tmp);
	if (!node)
	{
		free(tmp);
		return ;
	}
	ft_lstadd_back(envp, node);
}

void	export(t_list **envp, char ** params)
{
	int 	i;
	int 	index;
	t_list	*node;


	i = 0;
	while (params[i])
	{
		node = get_node_by_value(*envp, params[i]);
		if (node != NULL)
			actualize_node_value(node, params[i]);
		else
			add_new_env_var(envp, params[i]);
		i++;
	}
}

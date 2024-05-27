/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:55:40 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/27 12:30:01 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

static size_t	ft_strlen_until_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static t_list	*get_node_by_value(t_list *list, char *param)
{
	while (list)
	{
		if (ft_strncmp(((char *)(list->content)), param,
			ft_strlen_until_equal(param)) == 0)
		{
			if (((char *)(list->content))[ft_strlen_until_equal(param)] == '=')
				return (list);
		}
		list = list->next;
	}
	return (NULL);
}

static void	actualize_node_value(t_list *node, char *param)
{
	char	*tmp;

	tmp = ft_strdup(param);
	if (tmp)
	{
		free(node->content);
		node->content = tmp;
	}
}

static void	add_new_env_var(t_list **envp, char *param)
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

int	ft_strchr_index(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *) s;
	while (str[i])
	{
		if (str[i] == c % 256)
			return (i);
		i++;
	}
	if (str[i] == c % 256)
		return (i);
	return (-1);
}

int	minishell_export(t_list **envp, char **params)
{
	int		i;
	t_list	*node;
	int 	index;

	i = 0;
	while (params[i])
	{
		index = ft_strchr_index(params[i], '=');
		if (index >= 0)
		{
			if (index == 0 || ft_strchr("+-", params[i][index - 1]))
				return (1);
			node = get_node_by_value(*envp, params[i]);
			if (node != NULL)
				actualize_node_value(node, params[i]);
			else
				add_new_env_var(envp, params[i]);
		}
		else
		{
			if (ft_isdigit(params[i][0]))
				return (1);
			if (ft_strchr("+-", params[i][ft_strlen(params[i]) - 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

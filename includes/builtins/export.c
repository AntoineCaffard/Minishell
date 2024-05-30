/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:55:40 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/30 09:05:17 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

static int	manage_export_append(t_list *node, char *param, int len)
{
	char	*duplicata;
	char	*tmp;

	len --;
	if (!((char *)node->content)[len])
		duplicata = ft_strdup(&(param[len + 1]));
	else
		duplicata = ft_strdup(&(param[len + 2]));
	if (!duplicata)
		return (1);
	tmp = ft_strjoin(node->content, duplicata);
	if (!tmp)
	{
		free(duplicata);
		return (1);
	}
	free(node->content);
	free(duplicata);
	node->content = tmp;
	return (0);
}

static int	actualize_node_value(t_list *node, char *param)
{
	char	*tmp;
	int		length;
	int		error;

	length = ft_strlen_until_equal(param);
	if (param[length - 1] == '+')
	{
		error = manage_export_append(node, param, length);
		return (error);
	}
	tmp = ft_strdup(param);
	if (!tmp)
		return (1);
	free(node->content);
	node->content = tmp;
	return (0);
}

static int	manage_add_if_equals(char *param, t_list **envp, int index)
{
	int		error;
	t_list	*node;

	error = 0;
	if (index == 0 || param[index - 1] == '-')
		return (1);
	node = get_node_by_value_export(*envp, param);
	if (node != NULL)
		error = actualize_node_value(node, param);
	else
		error = add_new_env_var(envp, param);
	return (error);
}

static int	manage_add_if_new(char *param, t_list **envp)
{
	t_list	*node;
	int		error;

	error = 0;
	if (ft_isdigit(param[0]))
		return (1);
	if (ft_strchr("+-", param[ft_strlen(param) - 1]))
		return (1);
	node = get_node_by_value_export(*envp, param);
	if (node == NULL)
	{
		error = add_new_env_var(envp, param);
		if (error)
			return (error);
	}
	return (0);
}

int	minishell_export(t_list **envp, char **params)
{
	int		i;
	int		index;
	int		error;

	i = 0;
	error = 0;
	while (params[i])
	{
		index = ft_strchr_index(params[i], '=');
		if (index >= 0)
		{
			error = manage_add_if_equals(params[i], envp, index);
			if (error)
				return (error);
		}
		else
		{
			error = manage_add_if_new(params[i], envp);
			if (error)
				return (error);
		}
		i++;
	}
	return (0);
}

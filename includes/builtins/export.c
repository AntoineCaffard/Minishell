/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:55:40 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/28 13:53:11 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

size_t	ft_strlen_until_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static t_list	*get_node_by_value(t_list *list, char *param)
{
	int		length;
	char	*tmp;

	tmp = ft_strdup(param);
	if (!tmp)
		return (NULL);
	while (list)
	{
		length = ft_strlen_until_equal(tmp);
		if (tmp[length - 1] == '+')
			tmp[length - 1] = '=';
		if (ft_strncmp(((char *)(list->content)), tmp,
			ft_strlen_until_equal((char *)(list->content))) == 0)
		{
			if (((char *)(list->content))[ft_strlen_until_equal(tmp)] == '=' || !((char *)(list->content))[ft_strlen_until_equal(tmp)])
			{
				free(tmp);
				return (list);
			}
		}
		list = list->next;
	}
	free(tmp);
	return (NULL);
}

static void	actualize_node_value(t_list *node, char *param)
{
	char	*tmp;
	char	*duplicata;
	int		length;

	length = ft_strlen_until_equal(param);
	if (param[length - 1] == '+')
	{
		length --;
		if (!((char *)node->content)[length])
			duplicata = ft_strdup(&(param[length + 1]));
		else
			duplicata = ft_strdup(&(param[length + 2]));
		if (!duplicata)
			return ;
		tmp = ft_strjoin(node->content, duplicata);
		if (!tmp)
		{
			free(duplicata);
			return ;
		}
		free(node->content);
		free(duplicata);
		node->content = tmp;
		return ;
	}
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
			if (index == 0 || params[i][index - 1] == '-')
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
			node = get_node_by_value(*envp, params[i]);
			if (node == NULL)
				add_new_env_var(envp, params[i]);
		}
		i++;
	}
	return (0);
}

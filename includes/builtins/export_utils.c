/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:34:56 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/30 09:02:54 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

int	add_new_env_var(t_list **envp, char *param)
{
	char	*tmp;
	t_list	*node;

	tmp = ft_strdup(param);
	if (!tmp)
		return (1);
	node = ft_lstnew(tmp);
	if (!node)
	{
		free(tmp);
		return (1);
	}
	ft_lstadd_back(envp, node);
	return (0);
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

t_list	*get_node_by_value_export(t_list *list, char *param)
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
			if (((char *)(list->content))[ft_strlen_until_equal(tmp)] == '=' ||
				!((char *)(list->content))[ft_strlen_until_equal(tmp)])
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

size_t	ft_strlen_until_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

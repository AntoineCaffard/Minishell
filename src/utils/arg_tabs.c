/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tabs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:36:54 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 16:37:50 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_t_argssize(t_arglist *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_t_argssize(lst->next));
}

char	**init_t_args_in_stringtab(t_arglist *args)
{
	char		**res;
	int			size;
	int			i;
	t_arglist	*tmp;

	tmp = args;
	if (!tmp || !tmp->value)
		return (NULL);
	size = ft_t_argssize(tmp);
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (tmp)
	{
		res[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (res);
}

t_arglist	*init_stringtab_in_t_args(char **args)
{
	t_arglist	*res;
	int			i;

	if (!args)
		return (NULL);
	i = 0;
	res = ft_calloc(1, sizeof(t_list));
	res->value = ft_strdup(args[i]);
	i++;
	while (args[i])
	{
		ft_argpush(&res, ft_argnew(ft_strdup(args[i])));
		i++;
	}
	return (res);
}

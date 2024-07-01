/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_t_args_or_stringtab.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:27:01 by trebours          #+#    #+#             */
/*   Updated: 2024/05/27 11:27:37 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_t_argssize(t_argument *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_t_argssize(lst->next));
}

char	**init_t_args_in_stringtab(t_argument *args)
{
	char		**res;
	int			size;
	int			i;
	t_argument	*tmp;

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

t_argument	*init_stringtab_in_t_args(char **args)
{
	t_argument	*res;
	int			i;

	if (!args)
		return (NULL);
	i = 0;
	res = ft_calloc(1, sizeof(t_list));
	res->value = ft_strdup(args[i]);
	i++;
	while (args[i])
	{
		t_argument_add_back(&res, create_argument(ft_strdup(args[i])));
		i++;
	}
	return (res);
}

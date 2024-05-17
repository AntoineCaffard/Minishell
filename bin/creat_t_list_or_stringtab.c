/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_t_list_or_stringtab.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:39:23 by trebours          #+#    #+#             */
/*   Updated: 2024/04/24 15:28:11 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*init_stringtab_in_t_list(char **envp)
{
	t_list	*res;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	res = ft_calloc(1, sizeof(t_list));
	res->content = ft_strdup(envp[i]);
	i++;
	while (envp[i])
	{
		ft_lstadd_back(&res, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (res);
}

char	**init_t_list_in_stringtab(t_list	*envp)
{
	char	**res;
	int		size;
	int		i;

	if (!envp)
		return (NULL);
	size = ft_lstsize(envp);
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (envp)
	{
		res[i] = ft_strdup(envp->content);
		envp = envp->next;
		i++;
	}
	return (res);
}

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
	char	**res;
	int		size;
	int		i;

	if (!args)
		return (NULL);
	size = ft_t_argssize(args);
	res = ft_calloc(size + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (args)
	{
		res[i] = ft_strdup(args->value);
		args = args->next;
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

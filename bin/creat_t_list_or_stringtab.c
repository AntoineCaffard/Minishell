/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_t_list_or_stringtab.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:39:23 by trebours          #+#    #+#             */
/*   Updated: 2024/02/23 16:08:47 by trebours         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listify_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:30:07 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 16:31:45 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

t_list	*listify_str_array(char **envp)
{
	t_list	*res;
	int		i;

	if (!envp || !envp[0])
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

char	**tabify_list(t_list *envp)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tabs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:36:54 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/25 16:06:35 by trebours         ###   ########.fr       */
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
		if (tmp->value)
			res[i] = ft_strdup(tmp->value);
		else
			res[i] = ft_strdup("\0");
		tmp = tmp->next;
		i++;
	}
	return (res);
}

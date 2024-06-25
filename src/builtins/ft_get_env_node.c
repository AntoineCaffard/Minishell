/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:12:25 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/24 13:56:44 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

t_list	*ft_get_env_node(t_list *envp, char *var_name, int var_len)
{
	if(!envp || !var_name)
		return (NULL);
	while (envp)
	{
		if (ft_strncmp(envp->content, var_name, var_len) == 0)
		{
			if (((char *)(envp->content))[var_len] == '\0')
				return (envp);
			if (((char *)(envp->content))[var_len] == '=')
				return (envp);
		}
		envp = envp->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:30:03 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:07:16 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_unset(t_list **envp, char **arguments)
{
	size_t	iterator;
	size_t	var_len;
	int		del_index;
	t_list	*to_unset;

	iterator = 0;
	while (arguments[iterator])
	{
		var_len = ft_env_var_len(arguments[iterator]);
		to_unset = ft_get_env_node(*envp, arguments[iterator], var_len);
		if (to_unset != NULL)
		{
			del_index = ft_lst_get_index(*envp, to_unset);
			ft_lst_remove_index(envp, del_index);
		}
		iterator++;
	}
	return (0);
}

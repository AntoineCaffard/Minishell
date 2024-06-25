/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:26:52 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/24 16:27:50 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	update_env_var(t_list **envp, char *argument)
{
	t_list	*to_update;
	size_t	var_len;
	char	*tmp;

	var_len = ft_env_var_len(argument);
	to_update = ft_get_env_node(*envp, argument, var_len);
	if (!to_update)
		return (ft_add_new_node(envp, argument));
	if (!argument[var_len])
		return (0);
	tmp = ft_strdup(argument);
	if (!tmp)
		return (print_error(MALLOC_ERROR));
	free(to_update->content);
	to_update->content = tmp;
	return (0);
}

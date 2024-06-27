/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvondir <elvondir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:37:59 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/25 13:47:20 by elvondir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

size_t	ft_env_var_len(char *env_var)
{
	size_t	var_len;

	var_len = 0;
	while (env_var[var_len] && ft_isalpha(env_var[var_len]))
		var_len++;
	return (var_len);
}

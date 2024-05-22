/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:08 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 09:46:41 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

int	parsing_env(char **params, t_list *envp)
{
	if (ft_stringtab_len(params) > 0)
		display_error_cmd(2, "too many argument", NULL);
	else
		return (minishell_env(envp));
	return (1);
}

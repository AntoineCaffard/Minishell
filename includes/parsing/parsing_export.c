/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 09:44:54 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_export(t_list **envp, char **params)
{
	if (ft_stringtab_len(params) < 1)
		minishell_env(envp);
	if (count_occurences_in_string(params[1], '=') > 1)
		return ;
	else
		minishell_export(envp, params);
}

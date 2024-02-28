/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/28 11:24:14 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_export(t_list **envp, char **params)
{
	if (ft_stringtab_len(params) != 1)
		strerror(0); // a revoir
	if (count_occurences_in_string(params[1], '=') > 1)
		strerror(0); // a revoir
	else
		minishell_export(envp, params);
}

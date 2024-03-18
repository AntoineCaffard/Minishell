/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 09:46:26 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_export(t_list **envp, char **params)
{
	if (ft_stringtab_len(params) == 0)
		minishell_env(*envp);
	else if (count_occurences_in_string(params[1], '=') > 1)
		strerror(0); // a revoir
	else
		minishell_export(envp, params);
}

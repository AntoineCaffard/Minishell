/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:31 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/28 11:35:09 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_unset(t_list **envp, char **params)
{
	if (ft_stringtab_len(params) > 1)
		return ;
	else
		minishell_unset(envp, params);
}

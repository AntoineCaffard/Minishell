/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:08 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/28 11:25:32 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_env(char **params, t_list *envp)
{
	if (ft_stringtab_len(params) > 1)
		strerror(0); // a revoir
	else
		minishell_env(envp);
}

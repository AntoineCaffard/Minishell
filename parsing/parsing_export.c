/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 10:31:40 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_export(char **params)
{
	if (ft_stringtab_len(params) != 1)
		strerror(0); // a revoir
	if (count_char_in_string(params[1], '=') > 1)
		strerror(0); // a revoir
}

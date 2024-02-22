/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 14:24:56 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_export(char **params)
{
	if (ft_stringtab_len(params) != 1)
		strerror(0); // a revoir
	if (count_occurences_in_string(params[1], '=') > 1)
		strerror(0); // a revoir
}

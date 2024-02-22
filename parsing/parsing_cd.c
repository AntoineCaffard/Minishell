/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:24 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 11:17:17 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_cd(char **params)
{
	if (ft_stringtab_len(params) != 1)
		strerror(0); // a revoir
	if (!access(params[0], F_OK))
		strerror(0); // a revoir
	if (!access(params[0], R_OK))
		strerror(0); // a revoir
}

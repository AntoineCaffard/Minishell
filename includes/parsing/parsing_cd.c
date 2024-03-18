/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:24 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 08:26:48 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_cd(char **params)
{
	if (ft_stringtab_len(params) != 1)
		// strerror(0); // a revoir
		display_error_cmd(0, "too many or less argument", NULL);
	else if (access(params[0], F_OK))
		// strerror(0); // a revoir
		display_error_cmd(0, "no such file in directory", params[0]);
	else if (access(params[0], R_OK))
		display_error_cmd(0, "no such file in directory", params[0]);
		// strerror(0); // a revoir
	else
		minishell_cd(params[0]);
}

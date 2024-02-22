/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:20 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 11:14:51 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	verif_option_echo(char **params)
{
	if (ft_strnstr(params[0], "-n", ft_strlen(params[0])))
		parsing_echo(&params[1]);
	else
		parsing_echo(params);
}

void	parsing_echo(char **params)
{
	if (ft_stringtab_len(params) < 1)
		strerror(0); // a revoir
}

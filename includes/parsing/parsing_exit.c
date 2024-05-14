/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:04 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 09:35:31 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

int	parsing_exit(char **params)
{
	printf("exit\n");
	if (params && ft_stringtab_len(params) > 2)
	{
		display_error_cmd(4, "too many argument", NULL);
		return (0);
	}
	else if (params && ft_stringtab_len(params) > 1
		&& !ft_string_isdigit(params[1]))
		display_error_cmd(4, "not a digit", params[1]);
	return (1);
}

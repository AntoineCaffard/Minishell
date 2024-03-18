/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:04 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 08:25:32 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

int	parsing_exit(char *line)
{
	char	**params;

	params = ft_split_str(line, " ");
	if (params && ft_stringtab_len(params) > 1 && ft_string_isdigit(params[1]) == 0)
	{
		display_error_cmd(4, "not a digit", params[1]);
		return (0);
	}
	else if (params && ft_stringtab_len(params) > 2)
	{
		display_error_cmd(4, "too many argument", NULL); // a revoir
		return (0);
	}
	if (params)
		ft_free_stringtab(params);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:08 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 10:15:25 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_env(char **params)
{
	int	i;

	if (ft_stringtab_len(params) < 1)
		strerror(0); // a revoir
	i = 0;
	while (params[i])
	{
		if (count_occurences_in_string(param[i], '=') > 1)
		{
			strerror(0); // a revoir
			break;
		}
		i++;
	}
}

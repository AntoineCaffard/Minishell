/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:08 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 12:50:09 by acaffard         ###   ########.fr       */
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
		if (count_occurences_in_string(params[i], '=') > 1)
		{
			strerror(0); // a revoir
			break ;
		}
		i++;
	}
}

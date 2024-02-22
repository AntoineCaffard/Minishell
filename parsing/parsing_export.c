/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:38:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 10:06:51 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

int	count_occurences_in_string(const char *src, const char c)
{
	int	i;
	int	count;

	if (!src)
		return (0);
	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	parsing_export(char **params)
{
	if (ft_stringtab_len(params) != 1)
		strerror(0); // a revoir
	if (count_char_in_string(params[1], '=') > 1)
		strerror(0); // a revoir
}

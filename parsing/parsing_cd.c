/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:24 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 10:19:47 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

size_t	ft_stringtab_len(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	parsing_cd(char **params)
{
	if (ft_stringtab_len(params) != 1)
		strerror(0); // a revoir
	if (!access(params, F_OK))
		strerror(0); // a revoir
	if (!access(params, R_OK))
		strerror(0); // a revoir
}

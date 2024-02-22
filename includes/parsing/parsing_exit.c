/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:04 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 13:02:03 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

void	parsing_exit.c(char **params)
{
	if (ft_stringtab_len(params) > 1)
		strerror(0); // a revoir
}

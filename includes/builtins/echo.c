/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:52:49 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 14:01:20 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing_minishell.h"

void	my_echo(char **params)
{
	if (check_option(params) == 42)
		params++;
	while (*params)
	{
		printf("%s", *params);
		params++;
	}
	if (!check_option(params) == 42)
		printf("\n");
}

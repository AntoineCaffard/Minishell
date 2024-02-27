/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:52:49 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/26 14:33:31 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_echo(char **params)
{
	int	i;

	if (check_option(params) == 1)
	{
		if (!*params && params != NULL)
			free(params);
		return ;
	}
	i = 0;
	if (check_option(params) == 42)
		i++;
	while (params[i])
	{
		if (params[i + 1])
			printf("%s ", params[i]);
		else
			printf("%s", params[i]);
		i++;
	}
	if (check_option(params) != 42)
		printf("\n");
}

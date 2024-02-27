/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:52:49 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/27 10:57:59 by acaffard         ###   ########.fr       */
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
		ft_putstr_fd(params[i], STDOUT_FILENO);
		if (params[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (check_option(params) != 42)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

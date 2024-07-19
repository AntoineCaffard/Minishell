/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:07:48 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/19 15:20:48 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(char **params)
{
	size_t	i;

	i = 1;
	if (params[0][0] == '-')
	{
		while (params[0][i])
		{
			if (params[0][i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

static int	minishell_echo(char **params)
{
	size_t	i;
	int		check;

	if (params != NULL && !*params)
	{
		free(params);
		return (print_error((MALLOC_ERROR)));
	}
	i = 0;
	check = check_option(params);
	while (params[i] && check_option(&params[i]) == 1)
	{
		i++;
		check += check_option(&params[i]);
	}
	while (params[i])
	{
		ft_putstr_fd(params[i], STDOUT_FILENO);
		if (params[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (check == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	ft_echo(char **params)
{
	if (!params)
		return (print_error(MALLOC_ERROR));
	if (!*params)
	{
		printf("\n");
		return (0);
	}
	return (minishell_echo(params));
}

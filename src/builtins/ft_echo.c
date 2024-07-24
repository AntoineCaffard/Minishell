/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:07:48 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/24 12:13:54 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_if_ascii(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != 1)
			ft_putchar_fd(string[i], STDOUT_FILENO);
		i++;
	}
}

static int	check_option(char **params)
{
	size_t	i;

	i = 1;
	if (params[0] && params[0][0] == '-')
	{
		while (params[0][i])
		{
			if (params[0][i] != 'n')
				return (0);
			i++;
		}
		if (i == 1)
			return (0);
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
		print_if_ascii(params[i]);
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

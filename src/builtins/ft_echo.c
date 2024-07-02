/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:07:48 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/02 11:22:36 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(char **params)
{
	if (ft_strnstr(params[0], "-n", ft_strlen(params[0])))
		return (42);
	else
		return (0);
}

static int	minishell_echo(char **params)
{
	int	i;

	if (check_option(params) == 1)
	{
		if (!*params && params != NULL)
			free(params);
		return (0);
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
	else if (params && ft_stringtab_len(params) > 1 && check_option(params))
		return (minishell_echo(params));
	else if (params && ft_stringtab_len(params) && check_option(params) == 0)
		return (minishell_echo(params));
	return (0);
}

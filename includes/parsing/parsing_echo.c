/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:22:17 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 11:27:23 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_minishell.h"

int	check_option(char **params)
{
	if (ft_strnstr(params[0], "-n", ft_strlen(params[0])))
		return (42);
	else
		return (0);
}

void	parsing_echo(char **params)
{
	if (!params || !ft_stringtab_len(params))
		display_error_cmd(1, NULL, NULL);
	else if (params && ft_stringtab_len(params) > 1 && check_option(params))
		minishell_echo(params);
	else if (params && ft_stringtab_len(params) && check_option(params) == 0)
		minishell_echo(params);
	else
		return ;
}

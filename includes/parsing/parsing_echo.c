/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:20 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 13:23:32 by trebours         ###   ########.fr       */
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

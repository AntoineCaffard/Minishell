/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:34:34 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 11:17:36 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

int	minishell_cd(char *path)
{
	int	status;

	status = chdir(path);
	if (status != 0)
	{
		display_error("No such file or directory", path);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:34:34 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/27 14:41:53 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_cd(char *path)
{
	int	status;

	status = chdir(path);
	if (status != 0)
		return ; //error
}

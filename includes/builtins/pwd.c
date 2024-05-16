/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:01:25 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 11:01:51 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

void	minishell_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (!buffer)
		return ;
	printf("%s\n", buffer);
	free(buffer);
}

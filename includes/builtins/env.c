/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:40:06 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/28 10:28:25 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

int	minishell_env(t_list *envp)
{
	if (!envp)
		return (0);
	while (envp)
	{
		printf("%s\n", (char *) envp->content);
		envp = envp->next;
	}
	return (0);
}

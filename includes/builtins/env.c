/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:40:06 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/27 14:42:12 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_env(t_list *envp)
{
	if (!envp)
		return ;
	while (envp)
		printf("%s\n", (char *) envp->content);
}

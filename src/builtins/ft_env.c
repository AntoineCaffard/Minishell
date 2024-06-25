/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:42:33 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/24 15:44:35 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	minishell_env(t_list *envp)
{
	while (envp)
	{
		printf("%s\n", (char *) envp->content);
		envp = envp->next;
	}
	return (0);
}

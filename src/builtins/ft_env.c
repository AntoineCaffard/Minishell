/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:42:33 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/02 13:34:17 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errors.h"
#include "../../includes/builtins.h"

static int	minishell_env(t_list *envp)
{
	while (envp)
	{
		if (ft_strchr(envp->content, '='))
			printf("%s\n", (char *) envp->content);
		envp = envp->next;
	}
	return (0);
}

int	ft_env(char **params, t_list *envp)
{
	if (ft_stringtab_len(params) > 0)
		print_error(TOO_MUCH_ARG_ERROR);
	else
		return (minishell_env(envp));
	return (1);
}

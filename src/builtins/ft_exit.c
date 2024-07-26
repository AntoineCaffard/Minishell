/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:13:58 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/24 10:39:18 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_digit(char *src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
	{
		if (!ft_isdigit(src[i]) && src[i] != '-' && src[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

int	minishell_exit(t_cmdline *command, char ***cmd,
					t_list *envp, t_cmdline first)
{
	int	save;

	if (envp)
		ft_lstclear(&envp, free);
	free_struct(&first);
	rl_clear_history();
	if (cmd && cmd[0][1] != NULL && !is_digit(cmd[0][1]))
	{
		save = ft_atoi(cmd[0][1]);
		ft_free_stringtab(cmd[0]);
		exit(save % 256);
	}
	if (cmd)
		ft_free_stringtab(cmd[0]);
	exit(command->return_code);
}

int	ft_exit(char **params, t_cmdline *cmd)
{
	if (params && is_digit(params[1]))
	{
		write(2, "not a digit\n", 12);
		return (1);
	}
	else if (params && ft_stringtab_len(params) > 2)
		return (print_error(TOO_MUCH_ARG_ERROR) + 2);
	return (cmd->return_code);
}

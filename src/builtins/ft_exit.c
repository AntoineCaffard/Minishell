/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:13:58 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/15 11:03:36 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	minishell_exit(t_cmdline *command, char ***cmd, t_list *envp)
{
	int	save;

	if (envp)
		ft_lstclear(&envp, free);
	free_struct(command);
	clear_history();
	if (cmd && cmd[0][1] != NULL && ft_string_isdigit(cmd[0][1]))
	{
		save = ft_atoi(cmd[0][1]);
		ft_free_stringtab(cmd[0]);
		exit(save % 256);
	}
	if (cmd)
		ft_free_stringtab(cmd[0]);
	if (command->return_code == 2)
		exit(2);
	exit(0);
}

int	ft_exit(char **params)
{
	printf("exit\n");
	if (params && ft_stringtab_len(params) > 1) // verif les num avec - et +
	{
		write(2, "not a digit\n", 12);
		return (2);
	}
	else if (params && ft_stringtab_len(params) > 2)
		return (print_error(TOO_MUCH_ARG_ERROR));
	return (0);
}

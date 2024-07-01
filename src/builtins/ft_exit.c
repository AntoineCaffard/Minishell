/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:13:58 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 13:59:35 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	minishell_exit(t_cmdline *command, char ***cmd, t_list *envp)
{
	int	save;

	ft_lstclear(&envp, free);
	free_struct(command);
	clear_history();
	if (cmd && cmd[0][1] != NULL && ft_string_isdigit(cmd[0][1]))
	{
		save = ft_atoi(cmd[0][1]);
		ft_free_stringtab(cmd[0]);
		exit(save);
	}
	if (cmd)
		ft_free_stringtab(cmd[0]);
	exit(0);
}

int	ft_exit(char **params)
{
	printf("exit\n");
	if (params && ft_stringtab_len(params) > 2)
		return (print_error(TOO_MUCH_ARG_ERROR));
	else if (params && ft_stringtab_len(params) > 1
		&& !ft_string_isdigit(params[1]))
	{
		//display_error_cmd(4, "not a digit", params[1]);
		return (2);
	}
	return (0);
}

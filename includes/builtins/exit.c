/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:44:49 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/24 16:01:35 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

int	minishell_exit(t_command_line *command, char ***cmd, t_list *envp)
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

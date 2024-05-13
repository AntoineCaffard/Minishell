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

static void	free_value(t_argument *args)
{
	while (args)
	{
		free(args->value);
		args = args->next;
	}
}

void	minishell_exit(t_command_line *command, char **cmd, t_list *envp)
{
	int	save;

	ft_lstclear(&envp, free);
	free_value(command->commands->args);
	free(command->commands->args);
	free(command->commands);
	clear_history();
	if (cmd[1] != NULL && ft_string_isdigit(cmd[1]))
	{
		save = ft_atoi(cmd[1]);
		ft_free_stringtab(cmd);
		exit(save);
	}
	ft_free_stringtab(cmd);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:44:49 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/27 14:40:27 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_minishell.h"

void	minishell_exit(t_command_line *command, char **cmd, t_list *envp)
{
	int	save;

	ft_lstclear(&envp, free);
	free(command->commands->args->value);
	free(command->commands->args);
	free(command->commands);
	free(command);
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

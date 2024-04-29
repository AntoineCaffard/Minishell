/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:52:58 by Trebours          #+#    #+#             */
/*   Updated: 2024/04/29 13:34:03 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_value(t_argument *args)
{
	while (args)
	{
		free(args->value);
		args = args->next;
	}
}

void	free_struct(t_command_line	*command)
{
	free_value(command->commands->args);
	free(command->commands->args);
	free(command->commands);
	command->commands = NULL;
}

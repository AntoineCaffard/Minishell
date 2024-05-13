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

void	ft_delone_args(t_argument *args, void (*del)(void*))
{
	if (!args || !del)
		return ;
	del(args->value);
	free(args);
}

void	ft_clear_arg(t_argument *args, void (*del)(void*))
{
	if (!args || !del)
		return ;
	if ((args->next) != NULL)
		ft_clear_arg(args->next, del);
	ft_delone_args(args, del);
}

void	free_struct(t_command_line	*command)
{
	ft_clear_arg(command->commands->args, free);	
	free(command->commands);
	command->commands = NULL;
}

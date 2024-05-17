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

void	ft_delone_args(t_argument **args, void (*del)(void*))
{
	if (!args || !del || !*args)
		return ;
	del((*args)->value);
	free(*args);
}

void	ft_clear_arg(t_argument **args, void (*del)(void*))
{
	if (!args || !del || !*args)
		return ;
	if (((*args)->next) != NULL)
		ft_clear_arg(&(*args)->next, del);
	ft_delone_args(args, del);
}

void	ft_delone_redir(t_redir **redir, void (*del)(void*))
{
	if (!redir || !del || !*redir)
		return ;
	del((*redir)->link);
	free(*redir);
}

void	ft_clear_redir(t_redir **redir, void (*del)(void*))
{
	if (!redir || !del || !*redir)
		return ;
	if (((*redir)->next) != NULL)
		ft_clear_redir(&(*redir)->next, del);
	ft_delone_redir(redir, del);
}

void	free_struct(t_command_line	*line)
{
	t_command	*buffer;

	buffer = line->commands;
	while (buffer)
	{
		line->commands = buffer->next;
		ft_clear_arg(&buffer->args, free);
		ft_clear_redir(&(buffer->redirs), free);
		free(buffer);
		buffer = line->commands;
	}
	free(buffer);
	line->commands = NULL;
}

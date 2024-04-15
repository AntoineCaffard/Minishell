/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:27 by utilisateur       #+#    #+#             */
/*   Updated: 2024/04/15 13:54:29 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	management_fd(t_pipe *save_fd, int i)
{
	if (i == 0)
	{
		dup2(save_fd->save_first_fd[0], STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	}
	else if (i == save_fd->nmb_max_cmd - 1)
	{
		dup2(save_fd->save_fd, STDIN_FILENO);
		dup2(save_fd->save_first_fd[1], STDOUT_FILENO);
	}
	else if (i > 0)
	{
		dup2(save_fd->save_fd, STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	}
	else if (i == -1)
	{
		dup2(save_fd->save_first_fd[0], STDIN_FILENO);
		dup2(save_fd->save_first_fd[1], STDOUT_FILENO);
		close(save_fd->save_first_fd[0]);
		close(save_fd->save_first_fd[1]);
	}
}

int	ft_lst_command_size(t_command *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (1);
	return (1 + ft_lst_command_size(lst->next));
}

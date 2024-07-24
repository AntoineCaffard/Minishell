/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/24 06:43:41 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	verif_pipe_close(t_pipe *fds)
{
	int	index;

	if (!fds->index)
	{
		if (fds->pipe[0][1] != -1)
			close(fds->pipe[0][1]);
		fds->pipe[0][1] = -1;
		return ;
	}
	if (fds->index % 2)
		index = 1;
	else
		index = 0;
	if (fds->pipe[index][1] != -1)
		close(fds->pipe[index][1]);
	fds->pipe[index][1] = -1;
	if (index == 0)
		index++;
	else
		index--;
	if (fds->pipe[index][0] != -1)
		close(fds->pipe[index][0]);
	fds->pipe[index][0] = -1;
}

void	verif_pipe(t_pipe *fds)
{
	verif_pipe_close(fds);
	if (fds->pipe[0][0] == -1 && fds->pipe[0][1] == -1)
		pipe(fds->pipe[0]);
	if (fds->pipe[1][0] == -1 && fds->pipe[1][1] == -1)
		pipe(fds->pipe[1]);
}

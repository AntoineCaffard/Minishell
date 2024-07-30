/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:48:06 by trebours          #+#    #+#             */
/*   Updated: 2024/07/24 06:19:16 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	first(t_pipe *fds, int redirs)
{
	if (!redirs || redirs == 2)
	{
		dup2(fds->pipe[0][1], STDOUT_FILENO);
		close(fds->pipe[0][1]);
		fds->pipe[0][1] = -1;
	}
	else
	{
		close(fds->pipe[0][1]);
		fds->pipe[0][1] = -1;
	}
	close(fds->pipe[0][0]);
	fds->pipe[0][0] = -1;
}

static void	middle_input(int redirs, t_pipe *fds, int index)
{
	if (!redirs || redirs == 2)
	{
		dup2(fds->pipe[index][1], STDOUT_FILENO);
		close(fds->pipe[index][1]);
		fds->pipe[index][1] = -1;
	}
	else
	{
		close(fds->pipe[index][1]);
		fds->pipe[index][1] = -1;
	}
}

static void	middle(t_pipe *fds, int redirs)
{
	int	index;

	if (fds->index % 2)
		index = 1;
	else
		index = 0;
	middle_input(redirs, fds, index);
	if (!index)
		index++;
	else
		index--;
	if (!redirs || redirs == 1)
	{
		dup2(fds->pipe[index][0], STDIN_FILENO);
		close(fds->pipe[index][0]);
		fds->pipe[index][0] = -1;
	}
	else
	{
		close(fds->pipe[fds->index -1][0]);
		fds->pipe[fds->index - 1][0] = -1;
	}
}

void	end_cmd(t_pipe *fds, int redirs)
{
	int	index;

	if (fds->index % 2)
		index = 0;
	else
		index = 1;
	if (!redirs || redirs == 1)
	{
		dup2(fds->pipe[index][0], STDIN_FILENO);
		close(fds->pipe[index][0]);
		fds->pipe[index][0] = -1;
	}
	else
	{
		close(fds->pipe[fds->index -1][0]);
		fds->pipe[fds->index - 1][0] = -1;
	}
}

void	gestion_pipe(t_pipe *fds, int redirs)
{
	if (!fds->index)
		first(fds, redirs);
	else if (fds->index == fds->nmb_max_cmd - 1)
		end_cmd(fds, redirs);
	else
		middle(fds, redirs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:48:06 by trebours          #+#    #+#             */
/*   Updated: 2024/07/22 09:59:06 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	first(t_pipe *fds, t_redlist *redirs)
{
	if (!redirs || (redirs->type != REDIRECTION_APPEND
			&& redirs->type != REDIRECTION_OUTFILE))
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

static void	middle(t_pipe *fds, t_redlist *redirs)
{
	int	index;

	if (fds->index % 2)
		index = 1;
	else
		index = 0;
	if (!redirs || (redirs->type != REDIRECTION_APPEND
			&& redirs->type != REDIRECTION_OUTFILE))
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
	if (!index)
		index++;
	else
		index--;
	if (!redirs || (redirs->type != REDIRECTION_INFILE
			&& redirs->type != REDIRECTION_HEREDOC))
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

void	end_cmd(t_pipe *fds, t_redlist *redirs)
{
	int	index;

	if (fds->index % 2)
		index = 0;
	else
		index = 1;
	if (!redirs || (redirs->type != REDIRECTION_INFILE
			&& redirs->type != REDIRECTION_HEREDOC))
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

void	gestion_pipe(t_pipe *fds, t_redlist *redirs)
{
	if (!fds->index)
		first(fds, redirs);
	else if (fds->index == fds->nmb_max_cmd - 1)
		end_cmd(fds, redirs);
	else
		middle(fds, redirs);
}

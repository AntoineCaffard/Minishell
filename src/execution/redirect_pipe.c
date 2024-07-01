/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:48:06 by trebours          #+#    #+#             */
/*   Updated: 2024/07/01 16:20:43 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	first(t_pipe *fds, t_redlist *redirs)
{
	if (!redirs || (redirs->type != REDIRECTION_APPEND
			&& redirs->type != REDIRECTION_OUTFILE))
	{
		dup2(fds->pipe[fds->index][1], STDOUT_FILENO);
		close(fds->pipe[fds->index][1]);
		fds->pipe[fds->index][1] = -1;
	}
	else
	{
		close(fds->pipe[fds->index][1]);
		fds->pipe[fds->index][1] = -1;
	}
	close(fds->pipe[fds->index][0]);
	fds->pipe[fds->index][0] = -1;
}

static void	middle(t_pipe *fds, t_redlist *redirs)
{
	if (!redirs || (redirs->type != REDIRECTION_APPEND
			&& redirs->type != REDIRECTION_OUTFILE))
	{
		dup2(fds->pipe[fds->index][1], STDOUT_FILENO);
		close(fds->pipe[fds->index][1]);
		fds->pipe[fds->index][1] = -1;
	}
	else
	{
		close(fds->pipe[fds->index][1]);
		fds->pipe[fds->index][1] = -1;
	}
	if (!redirs || (redirs->type != REDIRECTION_INFILE
			&& redirs->type != REDIRECTION_HEREDOC))
	{
		dup2(fds->pipe[fds->index - 1][0], STDIN_FILENO);
		close(fds->pipe[fds->index -1][0]);
		fds->pipe[fds->index - 1][0] = -1;
	}
	else
	{
		close(fds->pipe[fds->index -1][0]);
		fds->pipe[fds->index - 1][0] = -1;
	}
}

void	gestion_pipe(t_pipe *fds, t_redlist *redirs)
{
	if (fds->index == 0)
		first(fds, redirs);
	else if (fds->index == fds->nmb_max_cmd - 1)
	{
		if (!redirs || (redirs->type != REDIRECTION_INFILE
				&& redirs->type != REDIRECTION_HEREDOC))
		{
			dup2(fds->pipe[fds->index - 1][0], STDIN_FILENO);
			close(fds->pipe[fds->index - 1][0]);
			fds->pipe[fds->index - 1][0] = -1;
		}
		else
		{
			close (fds->pipe[fds->index - 1][0]);
			fds->pipe[fds->index - 1][0] = -1;
		}
	}
	else if (fds->index < fds->nmb_max_cmd - 1)
		middle(fds, redirs);
}

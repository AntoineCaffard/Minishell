/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:34:10 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/17 12:29:33 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_redir(t_arglist *arg)
{
	if (arg->value[0] == '<' || arg->value[0] == '>')
		return (TRUE);
	return (FALSE);
}

t_arglist	*fill_r(t_cmdline *l, t_cmdlist *c, t_arglist *buf, t_list *e)
{
	t_redlist		*new_redir;

	if (!buf->next || is_redir(buf->next))
	{
		l->error_code = 1;
		write(2, "Minishell: syntax error\n", 25);
		return (NULL);
	}
	new_redir = ft_rednew(ft_redget_type(buf), buf->next->value);
	if (!new_redir)
		l->error_code = 1;
	buf = ft_argpop_two(&(c->args), buf);
	if (new_redir && new_redir->type == REDIRECTION_HEREDOC)
		l->error_code += ft_manage_heredoc(new_redir, e);
	ft_redpush(&(c->redirs), new_redir);
	return (buf);
}

void	fill_redirection(t_cmdline *line, t_list *envp)
{
	t_arglist	*buffer;
	t_cmdlist	*cmd;

	cmd = line->cmds;
	while (cmd)
	{
		buffer = cmd->args;
		while (buffer && line->error_code == 0)
		{
			if (is_redir(buffer))
				buffer = fill_r(line, cmd, buffer, envp);
			else
				buffer = buffer->next;
		}
		cmd = cmd->next;
	}
}

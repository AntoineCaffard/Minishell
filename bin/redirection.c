/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:35 by Trebours          #+#    #+#             */
/*   Updated: 2024/06/04 14:47:11 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_change_outfile(char *link, int i)
{
	int	fd;

	fd = -1;
	if (i == 1)
		fd = open(link, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (i == 2)
		fd = open(link, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	ft_change_infile(char *link)
{
	int	fd;

	if (!access(link, O_RDONLY))
		fd = open(link, O_RDONLY);
	else
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

void	main_redirection(t_command_line *cmd_line, int save_io[2], t_list *env)
{
	t_command	*cmd;
	t_redir		*current;
	t_redir		*next;

	cmd = cmd_line->commands;
	current = cmd->redirs;
	while (current && !cmd_line->error_code)
	{
		next = current->next;
		if (current->type == REDIRECTION_OUTFILE)
			cmd_line->error_code = ft_change_outfile(current->link, 1);
		else if (current->type == REDIRECTION_APPEND)
			cmd_line->error_code = ft_change_outfile(current->link, 2);
		else if (current->type == REDIRECTION_INFILE)
			cmd_line->error_code = ft_change_infile(current->link);
		else if (current->type == REDIRECTION_HEREDOC)
			ft_manage_heredoc(current->link, save_io, env);
		current = next;
	}
}

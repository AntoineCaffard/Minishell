/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:01:59 by trebours          #+#    #+#             */
/*   Updated: 2024/07/15 10:04:41 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	error_infile(char *link)
{
	write(2, "Minishell: ", 12);
	if (link)
		write(2, link, ft_strlen(link));
	write(2, ": No such file or directory\n", 29);
	return (0);
}

static void	loop_redirs(t_cmdline *cmd_line, t_redlist *current)
{
	if (current->type == REDIRECTION_OUTFILE)
		cmd_line->error_code = ft_change_outfile(current->link, 1);
	else if (current->type == REDIRECTION_APPEND)
		cmd_line->error_code = ft_change_outfile(current->link, 2);
	else if (current->type == REDIRECTION_INFILE)
		cmd_line->error_code = ft_change_infile(current->link);
	else if (current->type == REDIRECTION_HEREDOC)
	{
		dup2(current->heredoc_pipe[0], STDIN_FILENO);
		close(current->heredoc_pipe[0]);
	}
}

int	main_redirection(t_cmdline *cmd_line)
{
	t_cmdlist	*cmd;
	t_redlist	*current;
	t_redlist	*next;
	int			i;
	int			y;

	cmd = cmd_line->cmds;
	current = cmd->redirs;
	i = 0;
	y = 0;
	while (current && !cmd_line->error_code)
	{
		next = current->next;
		loop_redirs(cmd_line, current);
		if (current->type == REDIRECTION_APPEND
			|| current->type == REDIRECTION_OUTFILE)
			i = 1;
		if (cmd_line->error_code == 0 && (current->type == REDIRECTION_INFILE
				|| current->type == REDIRECTION_HEREDOC))
			y = 2;
		else
			y = error_infile(current->link);
		current = next;
	}
	return (i + y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:35 by Trebours          #+#    #+#             */
/*   Updated: 2024/04/15 13:21:10 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_outfile(char *link, int i)
{
	int	fd;

	fd = -1;
	if (i == 1)
		fd = open(link, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (i == 2)
		fd = open(link, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_change_infile(char *link)
{
	int	fd;

	fd = open(link, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	main_redirection(t_command_line *command)
{
	t_command 	*cmd;
	t_redir		*current;
	t_redir		*next;

	cmd = command->commands;
	current = cmd->redirs;
	while (current)
	{
		next = current->next;
		if (current->type == REDIRECTION_OUTFILE)
			ft_change_outfile(current->link, 1);
		else if (current->type == REDIRECTION_APPEND)
			ft_change_outfile(current->link, 2);
		else if (current->type == REDIRECTION_INFILE)
			ft_change_infile(current->link);
		else if (current->type == REDIRECTION_HEREDOC)
			ft_change_infile(current->link);
		current = next;
	}
}

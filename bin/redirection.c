/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:11:47 by trebours          #+#    #+#             */
/*   Updated: 2024/03/20 13:34:26 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	redirect_save_fd(int save_fd[2], int action)
{
	if (action == 1)
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
	}
	else if (action == 2)
	{
		dup2(save_fd[0], STDIN_FILENO);
		dup2(save_fd[1], STDOUT_FILENO);
		close(save_fd[0]);
		close(save_fd[1]);
	}
}

static int	isolate_cmd(char **line)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (!pos)
	{
		pos = locate_string_in_stringtab(&line[i], "<", 1);
		if (pos)
			break;
		if (line[pos][1] != '\0')
			i++;
		else
			i += 2;
	}
	while (pos != -1 && line[pos + i])
	{
		free(line[pos + i]);
		line[pos + i] = NULL;
		pos++;
	}
	return (i);
}

int	main_redirection(char **line, t_list *envp)
{
	int	i;
	int	save_fd[2];

	redirect_save_fd(save_fd, 1);
	if (redirect_input(line))
		return (1);
	i = isolate_cmd(line);
	if (line[i])
		ft_start_minishell(&line[i], &envp);
	redirect_save_fd(save_fd, 2);
	return (0);
}

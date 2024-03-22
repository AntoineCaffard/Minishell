/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:11:47 by trebours          #+#    #+#             */
/*   Updated: 2024/03/22 13:41:29 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_save_fd(int save_fd[2], int action)
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

void	loop_isolate_cmd(char **line, int pos, int i)
{
	while (pos != -1 && line[pos + i])
	{
		free(line[pos + i]);
		line[pos + i] = NULL;
		pos++;
	}
}

static int	isolate_cmd(char **line)
{
	int	i;
	int	pos_in;
	int	pos_out;

	i = 0;
	pos_in = 0;
	pos_out = 0;
	while (!pos_in || !pos_out)
	{
		pos_in = locate_string_in_stringtab(&line[i], "<", 1);
		pos_out = locate_string_in_stringtab(&line[i], ">", 1);
		if (pos_in && pos_out)
			break ;
		if ((pos_in != -1 && line[pos_in][1] != '\0')
			|| (pos_out != -1 && line[pos_out][1] != '\0'))
			i++;
		else
			i += 2;
	}
	if (pos_out > -1 && (pos_in == -1 || pos_in > pos_out))
		loop_isolate_cmd(line, pos_out, i);
	else
		loop_isolate_cmd(line, pos_in, i);
	return (i);
}

int	main_redirection(char **line, t_list *envp)
{
	int	i;
	int	save_fd[2];
	int	rsl_input;
	int	rsl_output;

	if (ft_parsing_output(line, ">", 1) > 0)
		return (1);
	redirect_save_fd(save_fd, 1);
	rsl_input = redirect_input(line);
	rsl_output = redirect_output(line);
	if (rsl_input && rsl_output)
	{
		redirect_save_fd(save_fd, 2);
		return (1);
	}
	i = isolate_cmd(line);
	if (line[i])
		ft_start_minishell(&line[i], &envp);
	redirect_save_fd(save_fd, 2);
	return (0);
}

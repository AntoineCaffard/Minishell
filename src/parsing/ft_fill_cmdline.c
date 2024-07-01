/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:29:32 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 10:20:39 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_command_end(char *line, int i)
{
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_quotes(line, i);
		else
			i++;
	}
	return (i);
}

static t_cmdlist	*manage_creation(t_cmdline *res)
{
	t_cmdlist	*command;

	command = ft_cmdnew();
	if (!command)
		res->error_code = 1;
	ft_cmdpush(&(res->cmds), command);
	return (command);
}

void	ft_fill_cmdline(t_cmdline *cmdline, char *line)
{
	int				i;
	bool			test_pipe;
	char			*tmp;
	t_cmdlist		*command;

	test_pipe = false;
	i = skip_spaces(line);
	if (line[i] == '\0')
		return ;
	i = get_command_end(line, i);
	if (line[i] == '|')
		test_pipe = TRUE;
	line[i] = '\0';
	command = manage_creation(cmdline);
	tmp = ft_strdup(line);
	if (!tmp || !command)
		return ;
	cmdline->error_code += fill_command(command, tmp);
	free(tmp);
	if (cmdline->error_code != 0)
		return ;
	if (test_pipe && cmdline->error_code == 0)
		ft_fill_cmdline(cmdline, &(line[i + 1]));
}

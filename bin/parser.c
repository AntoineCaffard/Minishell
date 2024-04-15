/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:21:53 by antoine           #+#    #+#             */
/*   Updated: 2024/04/15 11:46:40 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*fill_struct(t_command_line *res, char *line)
{
	int				i;
	bool			test_pipe;
	t_command		command;

	i = 0;
	test_pipe = FALSE;
	if (line[i] == '\0')
		return ;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|')
		test_pipe = TRUE;
	line[i] = '\0';
	command = create_command();
	fill_command(command, ft_strdup(line));
	if (test_pipe)
		fill_struct(res, &(line[i + 1]));
}

// fill_command

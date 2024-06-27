/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:29:32 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 15:32:21 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int get_pipe_index()

void	ft_fill_cmdline(t_cmdline *cmdline, char *line)
{
	int				i;
	bool			test_pipe;
	char			*tmp;
	t_command		*command;

	test_pipe = false;
	i = skip_spaces(line);
	if (line[i] == '\0')
		return ;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_quotes(line, i);
		else
			i++;
	}
	if (line[i] == '|')
		test_pipe = TRUE;
	line[i] = '\0';
	command = manage_creation(res);
	tmp = ft_strdup(line);
	if (!tmp || !command)
		return ;
	res->error_code += fill_command(command, tmp);
	free(tmp);
	if (res->error_code != 0)
		return ;
	if (test_pipe && res->error_code == 0)
		fill_struct(res, &(line[i + 1]));
}
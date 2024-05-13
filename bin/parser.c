/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:21:53 by antoine           #+#    #+#             */
/*   Updated: 2024/05/13 11:55:27 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_struct(t_command_line *res, char *line)
{
	int				i;
	bool			test_pipe;
	t_command		*command;

	i = 0;
	test_pipe = FALSE;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return ;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|')
		test_pipe = TRUE;
	line[i] = '\0';
	command = create_command();
	if (!command)
		return ;
	t_command_add_back(&(res->commands), command);
	res->error_code += fill_command(command, ft_strdup(line));
		if (res->error_code != 0)
			return ;
	if (test_pipe)
		fill_struct(res, &(line[i + 1]));
}

int	fill_command(t_command *cmd, char *line)
{
	int	i;
	int	j;
	t_argument	*arg;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return 1;
	if (line[i] == '<'|| line[i] == '>')
	{
		if(line[i + 1] == '<'|| line[i + 1] == '>')
			j = 2;
		else
			j = 1;
		arg = create_argument(ft_strndup(&line[i], j));
		if (!arg)
			return 1;
		t_argument_add_back(&(cmd->args), arg);
		fill_command(cmd, &(line[i + j]));
		return 0;
	}
	j = 0;
	if (line[i] == '$')
		j++;
	while (line[i + j] && !_is_separator(line[i + j]))
		j++;
	arg = create_argument(ft_strndup(&line[i], j));
	if (!arg)
		return 1;
	t_argument_add_back(&(cmd->args), arg);
	fill_command(cmd, &(line[i + j]));
	return (0);
}

int	fill_redirection(t_argument *res, t_redir *redir)
{
	t_redir		*new_redir;

	if (!res)
		return (0);
	if (is_redir(res))
	{
			if (!res->next || is_redir(res->next))
				return (1);
			else
			{
				new_redir = malloc(sizeof(t_redir));
				if (!new_redir)
					return (1);
				//new_redir->type = get_type()
				//suppr 2 element list chainee
				ft_lstadd_back(&redir , new_redir);
			}
	}
	//fill_redirection(next)
}


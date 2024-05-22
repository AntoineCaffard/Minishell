/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:21:53 by antoine           #+#    #+#             */
/*   Updated: 2024/05/22 11:19:19 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_struct(t_command_line *res, char *line)
{
	int				i;
	bool			test_pipe;
	char			*tmp;
	t_command		*command;

	test_pipe = FALSE;
	i = skip_spaces(line);
	if (line[i] == '\0')
		return ;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|')
		test_pipe = TRUE;
	line[i] = '\0';
	command = manage_creation(res);
	tmp = ft_strdup(line);
	if (!tmp || !command)
		return ;
	res->error_code += fill_command(command, tmp);
	if (res->error_code != 0)
		return ;
	if (test_pipe && res->error_code == 0)
		fill_struct(res, &(line[i + 1]));
	free(tmp);
}

static int	manage_redir(char *line, t_command *cmd, int i)
{
	int			j;
	t_argument	*arg;

	if (line[i + 1] == '<' || line[i + 1] == '>')
		j = 2;
	else
		j = 1;
	arg = create_argument(ft_strndup(&line[i], j));
	if (!arg)
		return (1);
	t_argument_add_back(&(cmd->args), arg);
	fill_command(cmd, &(line[i + j]));
	return (0);
}

int	fill_command(t_command *cmd, char *line)
{
	int			i;
	int			j;
	t_argument	*arg;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return (1);
	if (line[i] == '<' || line[i] == '>')
		return (manage_redir(line, cmd, i));
	j = 0;
	if (line[i] == '$')
		j++;
	if (line[i] == '\'' || line[i] == '\"')
		j = skip_quotes(line, i);
	while (line[i + j] && !minishell_is_separator(line[i + j]))
		j++;
	arg = create_argument(ft_strndup(&line[i], j));
	if (!arg)
		return (1);
	t_argument_add_back(&(cmd->args), arg);
	fill_command(cmd, &(line[i + j]));
	return (0);
}

static t_argument	*fill_r(t_command_line *l, t_command *c, t_argument *buf)
{
	t_redir		*new_redir;

	if (!buf->next || is_redir(buf->next))
		l->error_code = 1;
	new_redir = create_redir(get_type(buf), buf->next->value);
	if (!new_redir)
		l->error_code = 1;
	buf = remove_args_from_list(&(c->args), buf);
	if (!buf)
		l->error_code = 1;
	t_redir_add_back(&(c->redirs), new_redir);
	return (buf);
}

void	fill_redirection(t_command_line *line)
{
	t_argument	*buffer;
	t_command	*cmd;

	cmd = line->commands;
	while (cmd)
	{
		if (!cmd->args)
			line->error_code = 1;
		buffer = cmd->args;
		while (buffer && line->error_code == 0)
		{
			if (is_redir(buffer))
				buffer = fill_r(line, cmd, buffer);
			else
				buffer = buffer->next;
		}
		cmd = cmd->next;
	}
}

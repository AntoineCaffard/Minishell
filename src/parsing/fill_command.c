/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:15:13 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/19 14:12:10 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes//minishell.h"

static bool	minishell_is_separator(char c)
{
	if (is_space(c))
		return (true);
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

static int	get_argument_end(char *line, int i, int j)
{
	while (line[i + j] && !minishell_is_separator(line[i + j]))
	{
		if (line[i + j] == '\'' || line[i + j] == '\"')
			j += skip_quotes(line, i + j);
		else
			j++;
	}
	return (j);
}

static int	manage_redir(char *line, t_cmdlist *cmd, int i)
{
	int			j;
	t_arglist	*arg;

	if (line[i + 1] == line[i])
		j = 2;
	else
		j = 1;
	arg = ft_argnew(ft_strndup(&line[i], j));
	if (!arg)
		return (1);
	ft_argpush(&(cmd->args), arg);
	fill_command(cmd, &(line[i + j]));
	return (0);
}

int	fill_command(t_cmdlist *cmd, char *line)
{
	int			i;
	int			j;
	t_arglist	*arg;

	i = skip_spaces(line);
	if (!line[i])
		return (1);
	if (line[i] == '<' || line[i] == '>')
		return (manage_redir(line, cmd, i));
	j = 0;
	if (line[i] == '$')
		j++;
	j = get_argument_end(line, i, j);
	arg = ft_argnew(ft_strndup(&line[i], j));
	if (!arg)
		return (1);
	ft_argpush(&(cmd->args), arg);
	fill_command(cmd, &(line[i + j]));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:32:03 by trebours          #+#    #+#             */
/*   Updated: 2024/07/22 06:13:56 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_node(t_list *list, char *param)
{
	char	*tmp;
	char	*res;
	int		i;

	tmp = ft_strdup(get_value(list, param));
	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i] != '=' && tmp[i] != '\0')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (NULL);
	}
	i++;
	res = ft_strdup(&tmp[i]);
	free(tmp);
	return (res);
}

static char	*init_res(char *line, int i, t_list *envp, t_cmdline *cmd_line)
{
	char	*res;
	int		j;
	char	*save_first_part;
	char	*tmp;

	save_first_part = ft_strndup(line, i);
	j = i + 1;
	tmp = NULL;
	while (line[j])
	{
		if (!ft_isalnum(line[j]) || (line[j - 1] == '$' && line[j] == '?'))
			break ;
		j++;
	}
	if (line[j] == '?')
		return (get_return_value(&line, j, save_first_part, cmd_line));
	else
	{
		tmp = ft_strndup(&line[i + 1], j - i - 1);
		res = get_node(envp, tmp);
		res = add_cote(res);
		free(tmp);
		return (get_env_var(&line, j, save_first_part, res));
	}
}

static int	verif_char_expand(char c, char verif)
{
	if (ft_isalnum(c) || (!verif && (c == '\"' || c == '\'')) || c == '?')
		return (1);
	return (0);
}

static char	*expand(char *line, t_list *envp, t_cmdline *cmd_line)
{
	int		i;
	char	c;

	i = 0;
	if (!line || !line[i])
		return (NULL);
	c = 0;
	while (line && line[i])
	{
		if (!c && (line[i] == '\"' || line[i] == '\''))
			c = line[i];
		else if (c && line[i] == c)
			c = 0;
		else if (c != '\'' && line[i] == '$' && (line[i + 1]
				&& verif_char_expand(line[i + 1], c)))
		{
			line = init_res(line, i, envp, cmd_line);
			i = -1;
		}
		i++;
	}
	return (line);
}

void	main_expand(t_cmdline *cmd_line, t_list **envp)
{
	t_cmdlist	*cmd;
	t_cmdlist	*cmd_next;
	t_arglist	*current;
	t_redlist	*redirs;

	cmd = cmd_line->cmds;
	while (cmd)
	{
		cmd_next = cmd->next;
		current = cmd->args;
		redirs = cmd->redirs;
		while (current)
		{
			current->value = expand(current->value, (*envp), cmd_line);
			current = current->next;
		}
		while (redirs)
		{
			redirs->link = expand(redirs->link, (*envp), cmd_line);
			redirs = redirs->next;
		}
		cmd = cmd_next;
	}
	delete_quote(cmd_line->cmds);
}

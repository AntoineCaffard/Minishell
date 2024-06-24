/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:13:17 by trebours          #+#    #+#             */
/*   Updated: 2024/06/05 13:58:13 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_node(t_list *list, char *param)
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

char	*init_res(char *line, int i, t_list *envp, t_command_line *cmd_line)
{
	char	*res;
	int		j;
	char	*save_first_part;
	char	*save_end_part;
	char	*tmp;

	save_first_part = ft_strndup(line, i);
	j = i + 1;
	save_end_part = NULL;
	tmp = NULL;
	while (line[j])
	{
		if (!ft_isalnum(line[j]) || (line[j - 1] == '$' && line[j] == '?'))
			break;
		j++;
	}
	if (line[j] == '?')
		save_end_part = ft_strdup(&line[j + 1]);
	else
		save_end_part = ft_strdup(&line[j]);
	if (j == i + 1 && line[i + 1] != '?')
		return (ft_strjoin(save_end_part, save_end_part));
	if (line[i + 1] == '?')
		tmp = ft_itoa(cmd_line->return_value);
	if (!tmp)
	{
		res = ft_strndup(&line[i + 1], j - i - 1);
		tmp = get_node(envp, res);
		free(res);
	}
	res = ft_strjoin(save_first_part, tmp);
	if (tmp)
		free(tmp);
	free(save_first_part);
	if (save_end_part)
	{
		save_first_part = ft_strjoin(res, save_end_part);
		free(save_end_part);
		free(line);
		return (save_first_part);
	}
	free(line);
	return (res);
}

char	*expand(char *line, t_list *envp, t_command_line *cmd_line)
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
		else if (c != '\'' && line[i] == '$' && (line[i + 1] && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '?')))
			line = init_res(line, i, envp, cmd_line);
		i++;
	}
	return (line);
}

void	main_expand(t_command_line *cmd_line, t_list **envp)
{
	t_command	*cmd;
	t_command	*cmd_next;
	t_argument	*current;

	cmd = cmd_line->commands;
	while (cmd)
	{
		cmd_next = cmd->next;
		current = cmd->args;
		while (current)
		{
			current->value = expand(current->value, (*envp), cmd_line);
			current = current->next;
		}
		cmd = cmd_next;
	}
	delete_quote(cmd_line->commands);
}

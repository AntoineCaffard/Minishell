/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:13:17 by trebours          #+#    #+#             */
/*   Updated: 2024/05/17 10:41:50 by Trebours         ###   ########.fr       */
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
		return (NULL);
	i++;
	res = ft_strdup(&tmp[i]);
	free(tmp);
	return (res);
}

int	ft_stringtabchr(char **stringtab, char **line)
{
	int	i;

	free((*line));
	(*line) = ft_strdup("\0");
	i = 0;
	while (stringtab[i] && stringtab[i][0] != '$')
	{
		i++;
		if (!stringtab[i])
		{
			ft_free_stringtab(stringtab);
			return (-1);
		}
	}
	return (i);
}

char	*init_res(char **stringtab)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = "\0";
	while (stringtab[i])
	{
		tmp = ft_strjoin(res, stringtab[i]);
		if (res && res[0] != 0)
			free(res);
		if (stringtab[i + 1])
			res = ft_strjoin(tmp, " ");
		else
			res = ft_strdup(tmp);
		if (tmp)
			free(tmp);
		i++;
	}
	return (res);
}

char	*expand(char *line, t_list *envp)
{
	char	*res;
	char	**stringtab;
	int		i;

	if (ft_verif_var(line) == -1)
		return (line);
	stringtab = ft_split(line, ' ');
	i = ft_stringtabchr(stringtab, &line);
	if (i < 0)
		return (line);
	res = get_node(envp, &stringtab[i][1]);
	if (!res)
	{
		ft_free_stringtab(stringtab);
		return (line);
	}
	free(stringtab[i]);
	free(line);
	stringtab[i] = ft_strdup(res);
	free(res);
	res = init_res(stringtab);
	ft_free_stringtab(stringtab);
	return (res);
}

void	main_expand(t_command_line *cmd_line, t_list **envp)
{
	t_command	*cmd;
	t_command	*cmd_next;
	t_argument	*current;
	t_argument	*next;

	delete_cote(cmd_line);
	cmd = cmd_line->commands;
	while (cmd)
	{
		cmd_next = cmd->next;
		current = cmd->args;
		while (current)
		{
			next = current->next;
			current->value = expand(current->value, (*envp));
			current = next;
		}
		cmd = cmd_next;
	}
}

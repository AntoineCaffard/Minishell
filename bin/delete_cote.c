/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:54 by Trebours          #+#    #+#             */
/*   Updated: 2024/05/17 10:46:54 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	verif_cote(char **args, char c)
{
	int	i;
	int	j;

	j = 0;
	while (args[j])
	{
		i = 0;
		while (args[j][i])
		{
			if (!c && (args[j][i] == '\"' || args[j][i] == '\''))
				return (args[j][i]);
			else if (c && args[j][i] == c)
				return (args[j][i]);
			i++;
		}
		j++;
	}
	return (0);
}

static char	*remove_cote(char *str, char c)
{
	char *res;
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(&str[1]);
	if (str[len] == c)
		res = ft_strndup(&str[1], len - 1);
	else
		res = ft_strndup(&str[1], len);
	free(str);
	return (res);
}

static char **create_new_stringtab(char **current, char c)
{
	char	**new;
	int		i;
	int		j;
	int		save;
	char	*tmp;

	if (!current)
		return (NULL);
	i = 0;
	save = 0;
	while (current[i])
	{
		if (!save && ft_strchr(current[i], c))
			save = i + 1;
		if (save && ft_strchr(current[i], c) != ft_strrchr(current[i], c))
			break;
		if (!current[i])
			break;
		else
			i++;
	}
	if (save == i + 1)
	{	
		current[i] = remove_cote(current[i], c);
		return (current);
	}
	new = ft_calloc(ft_stringtab_len(current) - (i - save) + 1, sizeof(char *));
	j = 0;
	while (j < save - 1)
	{
		new[j] = ft_strdup(current[j]);
		j++;
	}
	new[j] = "\0";
	while (current[save - 1] && save <= i)
	{
		tmp = ft_strjoin(new[j], current[save - 1]);
		if (new[j][0] != 0)
			free(new[j]);
		if (save < i)
			new[j] = ft_strjoin(tmp, " ");
		else
			new[j] = ft_strdup(tmp);
		free(tmp);
		save++;
	}
	new[j] = remove_cote(new[j], c);
	j++;
	while (current[save - 1])
	{
		new[j] = ft_strdup(current[save - 1]);
		j++;
		save++;
	}
	ft_free_stringtab(current);
	return (new);
}

static t_argument	*recreate_args(t_argument *args)
{
	char		**args_stringtab;
	t_argument	*res;
	t_argument	*tmp;
	char		c;

	tmp = args;
	args_stringtab = init_t_args_in_stringtab(tmp);
	c = verif_cote(args_stringtab, 0);
	if (c != 0)
		args_stringtab = create_new_stringtab(args_stringtab, c);
	res = init_stringtab_in_t_args(args_stringtab);
	ft_clear_arg(&args, free);
	ft_free_stringtab(args_stringtab);
	return (res);
}

void	delete_cote(t_command_line *cmd_line)
{
	t_command	*cmd;
	t_command	*cmd_next;

	cmd = cmd_line->commands;
	while (cmd)
	{
		cmd_next = cmd->next;
		cmd->args = recreate_args(cmd->args);
		cmd = cmd_next;
	}
}

// a faire dans la creation des argument pour pouvoir gerder ou enlever les espaces entre cotes. exemple : "bonjour je suis "

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

static int	verif_cote(char **args)
{
	int	i;
	int	j;

	j = 0;
	while (args[j])
	{
		i = 0;
		while (args[j][i])
		{
			if (args[j][i] == '\"')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

static char	*remove_cote(char *str)
{
	char *res;
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(&str[1]);
	res = ft_strndup(&str[1], len - 1);
	free(str);
	return (res);
}

static char **create_new_stringtab(char **current)
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
		if (!save && ft_strchr(current[i], '\"'))
			save = i + 1;
		if (save && ft_strchr(current[i], '\"') != ft_strrchr(current[i], '\"'))
			break;
		if (!current[i])
			break;
		else
			i++;
	}
	if (save == i + 1)
	{	
		current[i] = remove_cote(current[i]);
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
	new[j] = remove_cote(new[j]);
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

	tmp = args;
	args_stringtab = init_t_args_in_stringtab(tmp);
	while (verif_cote(args_stringtab))
		args_stringtab = create_new_stringtab(args_stringtab);
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

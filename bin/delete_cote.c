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

int	ft_charchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *) s;
	i = 0;
	while (str[i])
	{
		if (str[i] == c % 256)
			return (i);
		i++;
	}
	if (str[i] == c % 256)
		return (i);
	return (-1);
}

static char	*remove_cote(char *str, char c)
{
	return (str);
}

static char **create_new_stringtab(char **current, char c)
{
	return (current);
}

static t_argument	*recreate_args(t_argument *args)
{
	return (args);
}

static t_redir	*recreate_redir(t_redir *reds)
{
	return (reds);
}

void	delete_cote(t_command_line *cmd_line)
{
	t_command	*cmd;
	t_command	*cmd_next;
	t_argument	*current_args;
	t_redir		*current_redir;

	cmd = cmd_line->commands;
	while (cmd)
	{
		cmd_next = cmd->next;
		current_args = cmd->args;
		current_redir = cmd->redirs;
		while(current_args)
		{
			current_args->value = recreate_args(current_args->value);
			current_args = current_args->next;
		}
		while (current_redir)
		{
			current_redir->link = recreate_redir(current_redir->link);
			current_redir = current_redir->next;
		}
		cmd = cmd_next;
	}
}

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

/* static int	verif_cote(char *args, char c)
{
	int	j;

	j = 0;
	while (args[j])
	{
		if (!c && (args[j] == '\"' || args[j] == '\''))
			return (args[j]);
		else if (c && args[j] == c)
			return (args[j]);
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
}*/

static char	*recreate_args_and_redir(char *args)
{
	// int	i;
	int		len;
	char	*res;

	res = NULL;
	len = ft_strlen(args);
	if ((args[0] == '\'' || args[0] == '\"') && (args[len - 1] == args[0]))
		res = ft_strndup(&args[1], len - 2);
	else if ((args[0] == '\'' || args[0] == '\"') && !ft_strrchr(args, args[0]))
		res = ft_strndup(&args[1], len - 1);
	else if (args[0] != '\'' && args[0] != '\"' && (args[len - 1] == args[0]))
		res = ft_strndup(args, len - 3);
	if (!res)
		return (args);
	free(args);
	return (res);
}

void	delete_cote(t_command *cmd)
{
	t_command	*cmd_next;
	t_argument	*current_args;
	t_argument	*next_args;
	t_redir		*current_redir;
	t_redir		*next_redir;

	while (cmd)
	{
		cmd_next = cmd->next;
		current_args = cmd->args;
		current_redir = cmd->redirs;
		while(current_args)
		{
			next_args = current_args->next;
			current_args->value = recreate_args_and_redir(current_args->value);
			current_args = next_args;
		}
		while (current_redir)
		{
			next_redir = current_redir->next;
			current_redir->link = recreate_args_and_redir(current_redir->link);
			current_redir = next_redir;
		}
		cmd = cmd_next;
	}
}

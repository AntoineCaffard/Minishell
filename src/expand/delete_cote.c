/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/22 05:24:17 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_charchr(const char *s, unsigned int y)
{
	char	*str;
	int		i;

	if (!s)
		return (-1);
	str = (char *) s;
	i = y;
	while (str[i])
	{
		if (str[i] == '\"' % 256 || str[i] == '\'' % 256)
			return (i);
		i++;
	}
	if (str[i] == '\"' % 256 || str[i] == '\'' % 256)
		return (i);
	return (-1);
}

static int	ft_charrchr(const char *s, unsigned int y)
{
	char	*str;
	char	c;
	int		i;

	if (!s)
		return (-1);
	str = (char *) s;
	i = ft_charchr(s, y);
	if (i == -1)
		return (-1);
	c = s[i];
	i++;
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

static char	*loop_recreate(int first_quote, int second_quote, char *args)
{
	char	*tmp;
	char	*tmp_2;
	char	*res;

	tmp = ft_strndup(args, first_quote);
	if (second_quote == -1)
	{
		free(args);
		return (tmp);
	}
	res = ft_strndup(&args[first_quote + 1], second_quote - first_quote - 1);
	tmp_2 = ft_strjoin(tmp, res);
	free(tmp);
	free(res);
	if (!args[second_quote] || !args[second_quote + 1])
	{
		free(args);
		return (tmp_2);
	}
	tmp = ft_strdup(&args[second_quote + 1]);
	res = ft_strjoin(tmp_2, tmp);
	free(tmp);
	free(tmp_2);
	free(args);
	return (res);
}

char	*recreate_args_and_redir(char *args)
{
	int		first_quote;
	int		second_quote;
	char	*res;

	if (!args)
		return (args);
	first_quote = ft_charchr(args, 0);
	second_quote = ft_charrchr(args, 0);
	if (first_quote == second_quote)
		return (args);
	if (second_quote < 0)
		second_quote = ft_strlen(args);
	res = loop_recreate(first_quote, second_quote, args);
	while (second_quote-- <= (int)ft_strlen(res)
		&& has_quotes(&res[second_quote]))
	{
		first_quote = ft_charchr(res, second_quote);
		second_quote = ft_charrchr(res, second_quote);
		if (second_quote < 0)
			second_quote = ft_strlen(res);
		res = loop_recreate(first_quote, second_quote, res);
	}
	return (res);
}

int	verif_quote(char *value)
{
	int len;

	if (!value)
		return (0);
	len = ft_strlen(value);
	if ((value[0] == '\"' || value[0] == '\'') && len == 1)
		return (1);
	else if (len == 2 && value[0] == '\"' && value[1] == '\"')
		return (1);
	else if (len == 2 && value[0] == '\'' && value[1] == '\'')
		return (1);
	return (0);
}

void	delete_quote(t_cmdlist *cmd)
{
	t_cmdlist	*cmd_next;
	t_arglist	*args;
	t_redlist	*redir;

	while (cmd)
	{
		cmd_next = cmd->next;
		args = cmd->args;
		redir = cmd->redirs;
		while (args)
		{
			if (verif_quote(args->value))
			{
				free(args->value);
				args->value = ft_strdup(" ");
			}
			else
				args->value = recreate_args_and_redir(args->value);
			args = args->next;
		}
		while (redir)
		{
			if (redir->type != REDIRECTION_HEREDOC)
				redir->link = recreate_args_and_redir(redir->link);
			redir = redir->next;
		}
		cmd = cmd_next;
	}
}

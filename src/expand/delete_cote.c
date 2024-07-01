/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:54 by Trebours          #+#    #+#             */
/*   Updated: 2024/06/05 13:58:58 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (args[second_quote + 1] == '\0')
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

static char	*recreate_args_and_redir(char *args)
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
	res = loop_recreate(first_quote, second_quote, args);
	while (res[second_quote - 1]
		&& verif_quote(&res[second_quote - 1]))
	{
		first_quote = ft_charchr(res, second_quote - 1);
		second_quote = ft_charrchr(res, second_quote - 1);
		res = loop_recreate(first_quote, second_quote, res);
	}
	return (res);
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
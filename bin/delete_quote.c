/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:46:54 by Trebours          #+#    #+#             */
/*   Updated: 2024/05/17 10:46:54 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	c;

	first_quote = ft_charchr(args, 0);
	second_quote = ft_charrchr(args, 0);
	if (first_quote == second_quote)
		return (args);
	c = args[first_quote];
	res = loop_recreate(first_quote, second_quote, args);
		printf("%d, %zu\n", second_quote, ft_strlen(res));
	while (res[second_quote - 1]
		&& verif_quote(&res[second_quote - 1]))
	{
		first_quote = ft_charchr(res, second_quote - 1);
		second_quote = ft_charrchr(res, second_quote - 1);
		res = loop_recreate(first_quote, second_quote, res);
		
	}
	return (res);
}

void	delete_quote(t_command *cmd)
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
		while (current_args)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:58:59 by trebours          #+#    #+#             */
/*   Updated: 2024/07/15 10:02:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_quotes(char *string)
{
	while (*string)
	{
		if ((*string == '\'') | (*string == '\"'))
			return (1);
		string++;
	}
	return (0);
}

static void	print_node_content(char *string, t_list *env)
{
	t_list	*node;
	int		i;

	if (!*string)
		return ;
	i = 0;
	node = ft_get_env_node(env, string, ft_strlen(string));
	if (!node)
		return ;
	while (((char *) node->content)[i] && ((char *) node->content)[i] != '=')
		i++;
	if (!((char *) node->content)[i])
		return ;
	i++;
	if (!((char *) node->content)[i])
		return ;
	printf("%s", &((char *) node->content)[i]);
}

static void	expand_and_print(char *string, t_list *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$' && (ft_isalnum(string[i + 1])
				|| string[i + 1] == '_'))
		{
			i++;
			j = 0;
			while (string[i + j] && (ft_isalnum(string[i + j])
					|| string[i + j] == '_'))
				j++;
			tmp = ft_strndup(&(string[i]), j);
			if (!tmp)
				return ;
			print_node_content(tmp, env);
			i += ft_strlen(tmp) - 1;
			free(tmp);
		}
		else
			printf("%c", string[i]);
		i++;
	}
	printf("\n");
}

static int	heredoc_loop_expand(t_redlist *redir, t_list *env, int save_io)
{
	int		test;
	char	*new_line;

	test = 1;
	dup2(save_io, STDOUT_FILENO);
	while (test)
	{
		new_line = readline("\033[1;33mheredoc: \033[0;m");
		if (g_return_value == 130)
			return (g_return_value);
		if (!new_line)
		{
			write(2, "minishell: warning: here-document at line 1 delimited by end-of-file\n", 70);
			signal(SIGINT, _sigint);
			return (0);
		}
		test = ft_strcmp(new_line, redir->link);
		dup2(redir->heredoc_pipe[1], STDOUT_FILENO);
		if (test)
			expand_and_print(new_line, env);
		dup2(save_io, STDOUT_FILENO);
		free(new_line);
	}
	return (0);
}

static int	heredoc_loop(t_redlist *redir, int save_io)
{
	int		test;
	char	*new_line;

	test = 1;
	dup2(save_io, STDOUT_FILENO);
	while (test)
	{
		new_line = readline("\033[1;33mheredoc: \033[0;m");
		if (g_return_value == 130)
			return (g_return_value);
		if (!new_line)
		{
			write(2, "minishell: warning: here-document at line 1 delimited by end-of-file\n", 70);
			signal(SIGINT, _sigint);
			return (0);
		}
		test = ft_strcmp(new_line, redir->link);
		dup2(redir->heredoc_pipe[1], STDOUT_FILENO);
		if (test)
			ft_printf("%s\n", new_line);
		dup2(save_io, STDOUT_FILENO);
		free(new_line);
	}
	return (0);
}

int	ft_manage_heredoc(t_redlist *redir, t_list *env)
{
	int	save_output;
	int	quotes_test;
	int	return_value;

	return_value = 0;
	quotes_test = has_quotes(redir->link);
	redir->link = recreate_args_and_redir(redir->link);
	if (!(redir->link))
		return (print_error(MALLOC_ERROR));
	signal(SIGINT, _sigintheredoc);
	pipe(redir->heredoc_pipe);
	save_output = dup(STDOUT_FILENO);
	if (quotes_test != 0)
		return_value = heredoc_loop_expand(redir, env, save_output);
	else
		return_value = heredoc_loop(redir, save_output);
	close(redir->heredoc_pipe[1]);
	dup2(save_output, STDOUT_FILENO);
	close(save_output);
	signal(SIGINT, _sigint);
	return (return_value);
}

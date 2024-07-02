/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:58:59 by trebours          #+#    #+#             */
/*   Updated: 2024/07/02 11:08:30 by acaffard         ###   ########.fr       */
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

static void expand_and_print(char *string, t_list *env)
{
	int		i;
	int		j;
	char 	*tmp;

	i = 0;

	while (string[i])
	{
		if (string[i] == '$' && (ft_isalpha(string[i + 1]) || string[i + 1] == '_'))
		{
			i++;
			j = 0;
			while (string[i + j] && (ft_isalpha(string[i + j]) || string[i + j] == '_'))
				j++;
			tmp = ft_strndup(&(string[i]), j);
			if (!tmp)
				return ;
			print_node_content(tmp, env);
			i += ft_strlen(tmp);
			free(tmp);
		}
		else
		{
			printf("%c", string[i]);
			i++;
		}
	}
	printf("\n");
}

int	ft_manage_heredoc(char *limiter, int save_io[2], t_list *env)
{
	char	*new_line;
	int		test;
	int		pipe_fds[2];
	int		save_output;

	signal(SIGINT, _sigintheredoc);
	test = 1;
	pipe(pipe_fds);
	save_output = dup(STDOUT_FILENO);
	dup2(save_io[1], STDOUT_FILENO);
	while (test)
	{
		new_line = readline("\033[1;33mheredoc: \033[0;m");
		if (RETURN_VALUE == 130)
			return (RETURN_VALUE);
		if (!new_line)
		{
			write(2, "minishell: warning: here-document at line 1 delimited by end-of-file\n", 70);
			signal(SIGINT, _sigint);
			return (0);
		}
		test = ft_strcmp(new_line, limiter);
		dup2(pipe_fds[1], STDOUT_FILENO);
		if (test)
			expand_and_print(new_line, env);
		dup2(save_io[1], STDOUT_FILENO);
		free(new_line);
	}
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	dup2(save_output, STDOUT_FILENO);
	close(pipe_fds[0]);
	close(save_output);
	signal(SIGINT, _sigint);
	return (0);
}

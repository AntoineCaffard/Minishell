/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:02:00 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/24 11:27:23 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*manage_line(t_cmdline *command_line, t_list *env)
{
	char	*prompt;
	char	*line;

	prompt = ft_prompt(command_line);
	if (!prompt)
	{
		chdir("..");
		return (manage_line(command_line, env));
	}
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		printf("exit\n");
		minishell_exit(command_line, NULL, env, *command_line);
	}
	if (!(line[0]))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	parse_minishell(t_cmdline *command_line, char *line, t_list *env)
{
	ft_fill_cmdline(command_line, line);
	if (!command_line->error_code)
		fill_redirection(command_line, env);
	free (line);
}

int	lexer_handler(t_cmdline *command_line, char *line, int lex_value)
{
	(void)line;
	if (lex_value)
		command_line->return_code = lex_value;
	return (lex_value);
}

int	verif_lexer(char *line, t_cmdline *command_line)
{
	int	i;

	i = lexer_handler(command_line, line, lexer(line));
	if (i)
	{
		if (!line[i])
			command_line->return_code = 0;
		else
			command_line->return_code = all_heredoc(line, i);
		return (1);
	}
	return (0);
}

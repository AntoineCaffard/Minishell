/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:02:00 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/15 10:11:45 by acaffard         ###   ########.fr       */
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
		minishell_exit(command_line, NULL, env);
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
	if (lex_value)
	{
		command_line->return_code = lex_value;
		free(line);
	}
	return (lex_value);
}

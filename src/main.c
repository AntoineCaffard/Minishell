/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:52 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 11:30:31 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	loop_main(t_cmdline *command_line, t_list *env, char *line) {

	//t_cmdline	cmd_buffer;
	int				i;

	(void) env;
	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		//if (!line)
			//minishell_exit(command_line, NULL, env);
		if (line && line[0] != '\0')
		{
			command_line->error_code = 0;
			add_history(line);
			i = lexer(line);
			if (i)
			{
				command_line->return_value = i;
				free(line);
				continue ;
			}
			ft_fill_cmdline(command_line, line);
			if (!command_line->error_code)
				fill_redirection(command_line);
			free (line);
			if (command_line->error_code)
			{
				command_line->return_value = command_line->error_code;
				free_struct(command_line);
				continue ;
			}
			free_struct(command_line);
		}
		else
			free(line);
		if (command_line->return_value == -1)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_cmdline	command_line;
	t_list			*env;
	char			*line;
	int				i;

	(void) ac;
	(void) av;
	i = 0;
	//signal(SIGINT, _sigint);
	//signal(SIGQUIT, SIG_IGN);
	if (envp)
		env = listify_str_array(envp);
	else
		env = NULL;
	command_line.cmds = NULL;
	command_line.error_code = 0;
	command_line.return_value = 0;
	line = NULL;
	i = loop_main(&command_line, env, line);
	ft_lstclear(&env, free);
	clear_history();
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:52 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/15 11:11:08 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	RETURN_VALUE = 0;

void	minishell_exec(t_cmdline *command_line, t_list *envp)
{
	t_cmdline	cmd_buffer;

	cmd_buffer = *command_line;
	main_expand(&cmd_buffer, &envp);
	cmd_buffer = *command_line;
	if (ft_verif_exit(&cmd_buffer, &envp))
		main_pipe(&cmd_buffer, &envp);
	command_line->return_code = cmd_buffer.return_code;
}

int	loop_main(t_cmdline *command_line, t_list *env, char *line)
{
	int	i;

	while (1)
	{
		free_struct(command_line);
		line = manage_line(command_line, env);
		if (!line)
			continue;
		command_line->error_code = 0;
		add_history(line);
		i = lexer_handler(command_line,line, lexer(line));
		if (i)
			continue ;
		parse_minishell(command_line, line, env);
		if (command_line->error_code)
			command_line->return_code = command_line->error_code;
		else
			minishell_exec(command_line, env);
		RETURN_VALUE = 0;
	}
	if (command_line->return_code == -1)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_cmdline		command_line;
	t_list			*env;
	char			*line;
	int				i;

	(void) ac;
	(void) av;
	i = 0;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
	if (envp[0] != NULL)
		env = listify_str_array(envp);
	else
		env = NULL;
	command_line.cmds = NULL;
	command_line.error_code = 0;
	command_line.return_code = 0;
	line = NULL;
	i = loop_main(&command_line, env, line);
	free_struct(&command_line);
	ft_lstclear(&env, free);
	clear_history();
	return (i);
}

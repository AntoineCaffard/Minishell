/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/30 09:27:34 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main_execution(const t_command *cmd_l, t_list *envp, t_pipe *pipe_fds, const int i)
{
	char	**cmd;
	int		error;

	cmd = init_t_args_in_stringtab(cmd_l->args);
	if (cmd == NULL)
		return (1);
	error = 0;
	if (!ft_strncmp(cmd[0], "echo", 5))
		error = parsing_echo(&cmd[1]);
	else if (!ft_strncmp(cmd[0], "env", 4))
		error = parsing_env(&cmd[1], envp);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		error = parsing_cd(&cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		minishell_pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		error = parsing_export(&envp, &cmd[1]);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		minishell_unset(&envp, &cmd[1]);
	else if (i == 0)
		error = execute_command(cmd, envp, pipe_fds);
	else
		error = execute_multi(cmd, envp, pipe_fds);
	ft_free_stringtab(cmd);
	return (error);
}

int	ft_verif_exit(t_command_line *command_line, t_list **envp)
{
	char	**cmd;

	if (ft_lst_command_size(command_line->commands) > 1)
		return (1);
	cmd = init_t_args_in_stringtab(command_line->commands->args);
	if (!cmd)
		command_line->return_value = 1;
	else if (!ft_strncmp(cmd[0], "exit", 5))
	{
		command_line->return_value = parsing_exit(cmd);
		if (!command_line->return_value)
			minishell_exit(command_line, &cmd, *envp);
	}
	else
	{
		ft_free_stringtab(cmd);
		return (1);
	}
	return (0);
}

int	loop_main(t_command_line *command_line, t_list *envp, char *line)
{
	t_command_line	cmd_buffer;
	int				i;

	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		if (!line)
			minishell_exit(command_line, NULL, envp);
		if (line && line[0] != '\0')
		{
			command_line->error_code = 0;
			add_history(line);
			i = lexer(line);
			if (i)
			{
				command_line->return_value = i;
				free(line);
				continue;
			}
			fill_struct(command_line, line);
			if (!command_line->error_code)
				fill_redirection(command_line);
			free (line);
			if (command_line->error_code)
			{
				command_line->return_value = command_line->error_code;
				free_struct(command_line);
				continue;
			}
			cmd_buffer = *command_line;
			main_expand(&cmd_buffer, &envp);
			cmd_buffer = *command_line;
			if (ft_verif_exit(&cmd_buffer, &envp))
				main_pipe(&cmd_buffer, &envp);
			command_line->return_value = cmd_buffer.return_value;
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
	t_command_line	command_line;
	t_list			*env;
	char			*line;
	int				i;

	(void) ac;
	(void) av;
	i = 0;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
	if (envp)
		env = init_stringtab_in_t_list(envp);
	else
		env = NULL;
	command_line.commands = NULL;
	command_line.error_code = 0;
	command_line.return_value = 0;
	line = NULL;
	i = loop_main(&command_line, env, line);
	ft_lstclear(&env, free);
	clear_history();
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/22 13:52:14 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_execution(t_command_line *command, t_list *envp)
{
	char	**cmd;

	cmd = init_t_args_in_stringtab(command->commands->args);
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd[0], "echo", 5))
		parsing_echo(&cmd[1]);
	else if (!ft_strncmp(cmd[0], "env", 4))
		parsing_env(&cmd[1], envp);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		parsing_cd(&cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		minishell_pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		parsing_export(&envp, &cmd[1]);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		minishell_unset(&envp, &cmd[1]);
	else
		execute_command(cmd, envp);
	ft_free_stringtab(cmd);
}

void	ft_verif_exit(t_command_line *command_line, t_list **envp)
{
	char	**cmd;

	if (ft_lst_command_size(command_line->commands) > 1)
		return ;
	else
	{
		cmd = init_t_args_in_stringtab(command_line->commands->args);
		if (!cmd)
			return ;
		if (!ft_strncmp(cmd[0], "exit", 5))
		{
			if (parsing_exit(cmd))
				minishell_exit(command_line, &cmd, *envp);
		}
		else
			ft_free_stringtab(cmd);
	}
}

void	loop_main(t_command_line *command_line, t_list *envp)
{
	t_command_line	cmd_buffer;
	char			*line;

	(void)command_line;
	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		if (!line)
			minishell_exit(command_line, NULL, envp);
		if (line && line[0] != '\0')
		{
			add_history(line);
			fill_struct(command_line, line);
			fill_redirection(command_line);
			free (line);
			cmd_buffer = *command_line;
			main_expand(&cmd_buffer, &envp);
			cmd_buffer = *command_line;
			ft_verif_exit(&cmd_buffer, &envp);
			main_pipe(&cmd_buffer, &envp);
			free_struct(command_line);
		}
		else
			free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_command_line	command_line;
	t_list			*env;

	(void) ac;
	(void) av;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
	env = init_stringtab_in_t_list(envp);
	command_line.commands = NULL;
	command_line.error_code = 0;
	loop_main(&command_line, env);
	ft_lstclear(&env, free);
}

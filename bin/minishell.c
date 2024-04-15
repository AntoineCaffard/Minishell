/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/09 15:07:27 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command_line	*init_command(char *line, t_command_line *rsl)
{
	if (!rsl)
		return (NULL);
	rsl->commands->args->value = strdup(line);
	return (rsl);
}

void	main_execution(t_command_line *command, t_list *envp)
{
	char **cmd;

	cmd = ft_split(command->commands->args->value, ' ');
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd[0], "exit", 5))
	{
		if (parsing_exit(cmd))
			minishell_exit(command, cmd, envp);
	}
	else if (!ft_strncmp(cmd[0], "echo", 5))
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_command_line	*command;
	t_list *env;

	(void) ac;
	(void) av;
	env = init_stringtab_in_t_list(envp);
	command = malloc(1 * sizeof(t_command_line));
	command->commands = malloc(1 * sizeof(t_command));
	command->commands->args = malloc(1 * sizeof(t_argument));
	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		add_history(line);
		if (line[0] != '\0')
		{
			init_command(line, command);
			free (line);
			main_execution(command, env);
			free(command->commands->args->value);
		}
		else
			free(line);
	}
	ft_lstclear(&env, free);
}

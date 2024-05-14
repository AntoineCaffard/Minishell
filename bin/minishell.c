/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/29 13:31:58 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_sigint()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	_sigquit()
{
	printf("\nbonjour\n");
}

void	main_execution(t_command_line *command, t_list *envp)
{
	char **cmd;

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

void	main_redirection(t_command_line *command)
{
	while (command->commands->redirs)
	{
		if (command->commands->redirs->type == REDIRECTION_OUTFILE)
			ft_change_outfile(command->commands->redirs->link, 1);
		else if (command->commands->redirs->type == REDIRECTION_APPEND)
			ft_change_outfile(command->commands->redirs->link, 2);
		else if (command->commands->redirs->type == REDIRECTION_INFILE)
			ft_change_infile(command->commands->redirs->link);
		else if (command->commands->redirs->type == REDIRECTION_HEREDOC)
			ft_change_infile(command->commands->redirs->link);
		command->commands->redirs = command->commands->redirs->next;
	}
}

void	main_pipe(t_command_line *command, t_list **envp)
{
	t_pipe	save_fd;

	save_fd.save_first_fd[0] = dup(STDIN_FILENO);
	save_fd.save_first_fd[1] = dup(STDOUT_FILENO);
	save_fd.nmb_max_cmd = ft_lst_command_size(command->commands);
	save_fd.save_fd = -1;
	_pipe(command, envp, &save_fd);
	management_fd(&save_fd, -1);
	close (save_fd.save_first_fd[0]);
	close (save_fd.save_first_fd[0]);
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_command_line	command_line;
	t_command_line	cmd_buffer;
	t_list *env;

	(void) ac;
	(void) av;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
	env = init_stringtab_in_t_list(envp);
	command_line.commands = NULL;
	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		if (!line)
			minishell_exit(&command_line, NULL, env);
		if (line && line[0] != '\0')
		{
			add_history(line);
			fill_struct(&command_line, line);
			free (line);
			cmd_buffer = command_line;
			ft_verif_exit(&cmd_buffer, &env);
			main_pipe(&cmd_buffer, &env);
			free_struct(&command_line);
		}
		else
			free(line);
	}
	ft_lstclear(&env, free);
}

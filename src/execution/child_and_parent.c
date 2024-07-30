/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:36:46 by trebours          #+#    #+#             */
/*   Updated: 2024/07/26 15:14:43 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/s_cmdlist.h"

void	parent(t_pipe *fds, t_cmdline *cmd_line, pid_t *pid)
{
	waitpid(pid[fds->index], &cmd_line->return_code, 0);
	if (cmd_line->return_code == 126 || cmd_line->return_code == 127)
		;
	else if (WIFSIGNALED(cmd_line->return_code))
		cmd_line->return_code = WTERMSIG(cmd_line->return_code) + 128;
	else if (WIFEXITED(cmd_line->return_code))
		cmd_line->return_code = WEXITSTATUS(cmd_line->return_code);
	fds->index--;
	while (fds->index >= 0)
	{
		waitpid(pid[fds->index], NULL, 0);
		fds->index--;
	}
}

void	child(t_cmdline *cmd_line, t_pipe *fds, t_list **envp, pid_t *pid)
{
	int	error;

	error = 0;
	free(pid);
	error = main_redirection(cmd_line);
	gestion_pipe(fds, error);
	close_pipe(fds);
	if (!cmd_line->error_code)
	{
		if (ft_verif_exit(cmd_line, envp, fds))
			error = main_execution(cmd_line->cmds, *envp, fds, 1);
		else
			error = cmd_line->error_code - 1;
		cmd_line->cmds = fds->save;
		free_struct(&fds->first);
		ft_lstclear(envp, free);
		rl_clear_history();
		exit(error);
	}
	rl_clear_history();
	ft_lstclear(envp, free);
	free_struct(&fds->first);
	exit(cmd_line->error_code);
}

int	main_execution(const t_cmdlist *cmd_l, t_list *envp,
					t_pipe *pipe_fds, const int i)
{
	char	**cmd;
	int		error;

	cmd = init_t_args_in_stringtab(cmd_l->args);
	if (cmd == NULL)
		return (0);
	error = 0;
	if (!ft_strncmp(cmd[0], "echo", 5))
		error = ft_echo(&cmd[1]);
	else if (!ft_strncmp(cmd[0], "env", 4))
		error = ft_env(&cmd[1], envp);
	else if (!ft_strncmp(cmd[0], "cd", 3))
		error = ft_cd(&envp, &cmd[1]);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd[0], "export", 7))
		error = ft_export(&envp, &cmd[1]);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(&envp, &cmd[1]);
	else if (i == 0)
		error = execute_command(cmd, envp, pipe_fds);
	else
		error = execute_multi(cmd, envp, pipe_fds);
	ft_free_stringtab(cmd);
	return (error);
}

static void	dup_free_exit(t_pipe *fds)
{
	dup2(fds->std_fd[0], STDIN_FILENO);
	dup2(fds->std_fd[1], STDOUT_FILENO);
	close(fds->std_fd[0]);
	close(fds->std_fd[1]);
	printf("exit\n");
}

int	ft_verif_exit(t_cmdline *command_line, t_list **envp, t_pipe *fds)
{
	char	**cmd;

	cmd = init_t_args_in_stringtab(command_line->cmds->args);
	if (!cmd && command_line->cmds->args)
		command_line->return_code = 1;
	else if (!cmd)
		return (1);
	else if (!ft_strncmp(cmd[0], "exit", 5))
	{
		if (fds->nmb_max_cmd == 1)
			dup_free_exit(fds);
		command_line->error_code = ft_exit(cmd, command_line);
		if (command_line->error_code != 3)
			minishell_exit(command_line, &cmd, *envp, fds->first);
		else
			ft_free_stringtab(cmd);
	}
	else
	{
		ft_free_stringtab(cmd);
		return (1);
	}
	return (0);
}

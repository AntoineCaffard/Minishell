/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:52 by trebours          #+#    #+#             */
/*   Updated: 2024/07/01 13:21:55 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_pipe
{
	int	**pipe;
	int	redirs;
	int	index;
	int	nmb_max_cmd;
	int	std_fd[2];
	t_cmdlist	*save;
}	t_pipe;

void	_sigint(int signaux);
void	_sigint_exec(int signaux);
void	_sigintheredoc(int signaux);
int	main_pipe(t_cmdline *cmd_line, t_list **envp);
void	parent(t_pipe *fds, t_cmdline *cmd_line, pid_t *pid);
void	child(t_cmdline *cmd_line, t_pipe *fds, t_list **envp, pid_t *pid);


# endif

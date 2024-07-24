/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:52 by trebours          #+#    #+#             */
/*   Updated: 2024/07/19 11:14:27 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_pipe
{
	int			**pipe;
	int			redirs;
	int			index;
	int			nmb_max_cmd;
	int			std_fd[2];
	t_cmdlist	*save;
}	t_pipe;

void	_sigint(int signaux);
void	_sigint_exec(int signaux);
void	_sigintheredoc(int signaux);
void	_signquit(int signaux);
int		main_pipe(t_cmdline *cmd_line, t_list **envp);
void	parent(t_pipe *fds, t_cmdline *cmd_line, pid_t *pid);
void	child(t_cmdline *cmd_line, t_pipe *fds, t_list **envp, pid_t *pid);
void	delete_quote(t_cmdlist *cmd);
char	*get_return_value(char **line, int j,
			char *first, t_cmdline *cmd_line);
void	main_expand(t_cmdline *cmd_line, t_list **envp);
int		main_redirection(t_cmdline *cmd_line);
char	*init_link(char *src, char **path, int *error);
char	**init_path(t_list *envp);
int		multi_command(char **cmd, char **envp, t_pipe *pipe_fds);
int		execute_multi(char **line, t_list *t_envp, t_pipe *pipe_fds);
int		verif_stat(char **line, char **path);
int		execute_command(char **line, t_list *t_envp, t_pipe *pipe_fds);
int		ft_manage_heredoc(t_redlist *redir, t_list *env);
void	close_pipe(t_pipe *fds);
void	gestion_pipe(t_pipe *fds, t_redlist *redirs);
int		main_execution(const t_cmdlist *cmd_l, t_list *envp,
			t_pipe *pipe_fds, const int i);
int		ft_verif_exit(t_cmdline *command_line, t_list **envp);
int		has_quotes(char *string);
char	*get_value(t_list *list, char *param);
char	*get_env_var(char **line, int j, char *first, char *var);
char	*recreate_args_and_redir(char *args);
int		ft_charchr(const char *s, unsigned int y);
char	*add_cote(char *src);
int		all_heredoc(char *line, int error_index);
char	**init_heredoc(char *line);
char	*creat_limiteur(char *line, int y);
int		is_alnum(char c);
int		has_quotes(char *string);

#endif

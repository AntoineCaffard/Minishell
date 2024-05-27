/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:57:27 by acaffard          #+#    #+#             */
/*   Updated: 2024/05/22 13:49:02 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include <term.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <curses.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "LIBFT/libft.h"
# include "parsing/parsing_minishell.h"
# include "builtins/builtins_minishell.h"

char		**main_parseur(char *line);
int			execute_command(char **line, t_list *t_envp);
t_list		*init_stringtab_in_t_list(char **envp);
char		**init_t_list_in_stringtab(t_list	*envp);
char		**init_t_args_in_stringtab(t_argument *args);
void		display_error(char *prompt, char *file_or_cmd);
void		display_error_cmd(int cmd, char *prompt, char *file);
void		management_fd(t_pipe *save_fd, int i);
void		ft_change_outfile(char *link, int i);
void		ft_change_infile(char *link);
int			ft_lst_command_size(t_command *lst);

int			fill_command(t_command *cmd, char *line);

t_command	*create_command(void);
t_command	*t_command_get_last(t_command *lst);
void		t_command_add_back(t_command **lst, t_command *new_tail);

t_argument	*create_argument(char *content);
t_argument	*t_argument_get_last(t_argument *lst);
void		t_argument_add_back(t_argument **lst, t_argument *new_tail);
t_argument	*remove_args_from_list(t_argument **args, t_argument *node);

t_redir		*create_redir(t_redirection_type type, char *link);
t_redir		*t_redir_get_last(t_redir *lst);
void		t_redir_add_back(t_redir **lst, t_redir *tail);

void		fill_struct(t_command_line *res, char *line);
void		fill_redirection(t_command_line *line);
t_command	*manage_creation(t_command_line *res);
int			skip_spaces(char *s);
int			skip_quotes(char *line, int i);

bool		is_space(char c);
bool		minishell_is_separator(char c);
bool		is_redir(t_argument *arg);

char		*ft_strndup(const char *s, size_t n);
void		free_struct(t_command_line	*command);
void		ft_delone_args(t_argument **args, void (*del)(void*));
void		_pipe(t_command_line *command, t_list **envp, t_pipe *save_fd);
void		main_redirection(t_command_line *command);
void		main_execution(t_command_line *command, t_list *envp);
void		_sigint(int signaux);
void		main_redirection(t_command_line *command);
void		main_pipe(t_command_line *command, t_list **envp);
// rajouter
int			lexer(char *string);
char		*expand(char *line, t_list *envp, t_command_line *cmd_line);
int			ft_verif_exit(t_command_line *command_line, t_list **envp);
void		main_expand(t_command_line *cmd_line, t_list **envp);
char		*get_value(t_list *list, char *param);
int			ft_verif_var(char *line);
void		delete_cote(t_command_line *cmd_line);
t_argument	*init_stringtab_in_t_args(char **args);
void		ft_clear_arg(t_argument **args, void (*del)(void*));
int			print_sort_list(t_list *list);
void		ft_clear_redir(t_redir **redir, void (*del)(void*));

#endif

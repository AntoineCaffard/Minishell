/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:57:27 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/15 11:30:38 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef enum e_error
{
	NONE,
	MALLOC_ERROR
}	t_error;

typedef enum e_redirection_type
{
	REDIRECTION_OUTFILE,
	REDIRECTION_INFILE,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC
}	t_redirection_type;

typedef struct s_argument
{
	char				*value;
	struct s_argument	*next;
}	t_argument;

typedef struct s_redirection
{
	t_redirection_type		type;
	char					*link;
	struct s_redirection	*next;
}	t_redir;

typedef struct s_command
{
	t_argument			*args;
	t_redirection		*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_command_line
{
	int			error_code;
	t_command	*commands;
}	t_command_line;

char			**main_parseur(char *line);
void			execute_command(char **line, t_list *envp);
t_list			*init_stringtab_in_t_list(char **envp);
char			**init_t_list_in_stringtab(t_list	*envp);
void			display_error(char *prompt, char *file_or_cmd);
void			display_error_cmd(int cmd, char *prompt, char *file);

t_command		*create_command(void);
t_command		*t_command_get_last(t_command *lst);
void			t_command_add_back(t_command **lst, t_command *new_tail);

t_argument		*create_argument(char *content);
t_argument		*t_argument_get_last(t_argument *lst);
void			t_argument_add_back(t_argument **lst, t_argument *new_tail);

t_redir			*create_redir(e_redirection_type type, char *link);
t_redir			*t_redir_get_last(t_redir *lst);
void			t_redir_add_back(t_redir **lst, t_redir *tail);

#endif

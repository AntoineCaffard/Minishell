/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:02:38 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 11:49:24 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_pipe
{
    int     save_fd;
    int     pipe[2];
    int     nmb_max_cmd;
    int     save_first_fd[2];
}t_pipe;

# include <term.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <curses.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "LIBFT/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include "parsing/parsing_minishell.h"
# include "builtins/builtins_minishell.h"

char	**init_path(t_list *envp);
char	*init_link(char *src, char **path);
void    main_pipe(char *line, t_list *envp);
char	**ft_split_modif(char *src, char c);
t_list	*init_stringtab_in_t_list(char **envp);
void	execute_command(char **line, t_list *envp);
char	**init_t_list_in_stringtab(t_list	*envp);
int		main_redirection(char **line, t_list *envp);
void	parsing_readline(char *line, t_list **envp);
void	display_error(char *prompt, char *file_or_cmd);
void	ft_start_minishell(char **line, t_list **envp);
int		compare_string_to_character(char *line, char chr);
void	display_error_cmd(int cmd, char *prompt, char *file);
void	heredoc(char **params,t_list **envp);

#endif

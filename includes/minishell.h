/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:12:40 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 16:54:14 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <term.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <curses.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "s_cmdlist.h"
# include "builtins.h"
# include "errors.h"
# include "utils.h"
# include "parsing.h"
# include "execution.h"

int		return_value;
char	*manage_line(t_cmdline *command_line, t_list *env);
void	parse_minishell(t_cmdline *command_line, char *line);
int 	lexer_handler(t_cmdline *command_line, char *line, int lex_value);

#endif

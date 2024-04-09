/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:57:27 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/09 14:42:22 by acaffard         ###   ########.fr       */
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

typedef enum e_error
{
	NONE,
	MALLOC_ERROR
} t_error;

typedef enum e_redirection_type
{
	REDIRECTION_OUTFILE,
	REDIRECTION_INFILE,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC
} t_redirection_type;

typedef struct s_argument
{
	char	*value;
	struct s_argument	*next;
}	t_argument;

typedef struct s_redirection
{
	t_redirection_type	type;
	char	*link;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	t_argument	*args;
	t_redirection	*redirs;
	struct s_command	*next;
} t_command;

typedef struct s_command_line
{
	int	error_code;
	t_command	*commands;
}	t_command_line;

#endif

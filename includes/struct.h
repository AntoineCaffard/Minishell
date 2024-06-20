/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:47:36 by trebours          #+#    #+#             */
/*   Updated: 2024/05/14 14:43:43 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

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
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_command_line
{
	int			error_code;
	int			return_value;
	t_command	*commands;
}	t_command_line;

typedef struct s_int_list
{
	int				content;
	struct s_int_list	*next;
}	t_int_list;

typedef struct s_pipe
{
	int	previous;
	int	pipe1[2];
	int	pipe2[2];
	int	redirs;
	int	index;
	int	nmb_max_cmd;
	int	std_fd[2];
}	t_pipe;

t_redirection_type	get_type(t_argument *arg);

# endif

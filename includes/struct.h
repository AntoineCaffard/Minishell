/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:47:36 by trebours          #+#    #+#             */
/*   Updated: 2024/04/23 12:47:38 by trebours         ###   ########.fr       */
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
	t_command	*commands;
}	t_command_line;

typedef struct s_pipe
{
	int	save_fd;
	int	pipe[2];
	int	nmb_max_cmd;
	int	save_first_fd[2];
}	t_pipe;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:02:38 by trebours          #+#    #+#             */
/*   Updated: 2024/02/27 15:48:00 by trebours         ###   ########.fr       */
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

t_list	*init_stringtab_in_t_list(char **envp);
void	execute_command(char **line, t_list *envp);
char	**init_t_list_in_stringtab(t_list	*envp);
void	parsing_readline(char *line, t_list **envp);
void	ft_start_minishell(char **line, t_list **envp);

#endif

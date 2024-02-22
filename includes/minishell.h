/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:02:38 by trebours          #+#    #+#             */
/*   Updated: 2024/02/22 11:16:54 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <termios.h>
# include <curses.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"
# include "parsing/parsing_minishell.h"

char	**ft_split_modif(char *src, char c);

#endif

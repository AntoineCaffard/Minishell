/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:02:38 by trebours          #+#    #+#             */
/*   Updated: 2024/02/21 11:19:03 by trebours         ###   ########.fr       */
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
# include "pipex/pipex.h"
# include "libft/libft.h"

char	**ft_split_modif(char *src, char c);

#endif

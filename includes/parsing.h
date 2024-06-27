/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:51:39 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 18:22:34 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "utils.h"
# include "minishell.h"

int		lexer(char *string);
void	fill_redirection(t_cmdline *line);
void	ft_fill_cmdline(t_cmdline *cmdline, char *line);
int		fill_command(t_cmdlist *cmd, char *line);

#endif
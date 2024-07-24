/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:51:48 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 16:38:22 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

int			skip_quotes(char *line, int i);
char		*ft_prompt(t_cmdline *cmdline);
char		**tabify_list(t_list *envp);
t_list		*listify_str_array(char **envp);
bool		is_space(char c);
int			skip_spaces(char *s);
char		**init_t_args_in_stringtab(t_arglist *args);
int			verif_lexer(char *line, t_cmdline *command_line);
void		del_cote(t_arglist **args);
int			verif_quote(char *value);

#endif

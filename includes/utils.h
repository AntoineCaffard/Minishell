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

int		skip_quotes(char *line, int i);
char	*ft_prompt(t_cmdline *cmdline);
char	**tabify_list(t_list *envp);
t_list	*listify_str_array(char **envp);
bool	is_space(char c);
int		skip_spaces(char *s);
t_arglist	*init_stringtab_in_t_args(char **args);
char	**init_t_args_in_stringtab(t_arglist *args);

#endif

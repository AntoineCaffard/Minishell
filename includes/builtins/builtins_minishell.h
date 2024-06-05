/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_minishell.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:20:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/04 15:01:58 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_MINISHELL_H
# define BUILTINS_MINISHELL_H

# include "../minishell.h"

int		minishell_cd(char *path);
int		minishell_echo(char **params);
int		minishell_env(t_list *envp);
int		minishell_exit(t_command_line *command, char ***cmd, t_list *envp);
void	minishell_pwd(void);
void	minishell_unset(t_list **envp, char **params);
int		minishell_export(t_list **envp, char **params);

t_list	*get_node_by_value_export(t_list *list, char *param);
t_list	*get_node_by_value(t_list *list, char *param);
int		add_new_env_var(t_list **envp, char *param);
int		ft_strchr_index(const char *s, int c);

#endif

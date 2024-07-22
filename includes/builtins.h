/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:56:45 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 16:40:34 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "LIBFT/libft.h"
# include "errors.h"
# include "s_cmdlist.h"

int		ft_add_new_node(t_list **list, char *value);
int		ft_print_sorted_env(t_list *list);
int		ft_append_node(t_list **envp, char *argument);
int		ft_export(t_list **envp, char **arguments);
int		update_env_var(t_list **envp, char *argument);
int		switch_directory(char *path, t_list **envp);
int		ft_cd(t_list **envp, char **arguments);
int		minishell_exit(t_cmdline *command, char ***cmd, t_list *envp);
int		ft_pwd(void);
int		ft_exit(char **params, t_cmdline *cmd);
size_t	ft_env_var_len(char *env_var);
t_list	*ft_get_env_node(t_list *envp, char *var_name, int var_len);
int		ft_echo(char **params);
int		ft_unset(t_list **envp, char **arguments);
int		ft_env(char **params, t_list *envp);

#endif

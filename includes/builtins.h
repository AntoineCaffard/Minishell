/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:56:45 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:41:13 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "LIBFT/libft.h"
# include "errors.h"

int		ft_add_new_node(t_list **list, char *value);
int		ft_print_sorted_env(t_list *list);
int		ft_append_node(t_list **envp, char *argument);
int		ft_export(t_list **envp, char **arguments);
int		update_env_var(t_list **envp, char *argument);
int		switch_directory(char *path, t_list **envp);
int		ft_cd(t_list **envp, char **arguments);
int		ft_pwd(void);
size_t	ft_env_var_len(char *env_var);
t_list	*ft_get_env_node(t_list *envp, char *var_name, int var_len);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_minishell.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:20:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 11:29:11 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_MINISHELL_H
# define BUILTINS_MINISHELL_H

# include "../minishell.h"

void	minishell_cd(char *path);
void	minishell_echo(char **params);
void	minishell_env(t_list *envp);
void	minishell_exit(t_command_line *command, char ***cmd, t_list *envp);
void	minishell_pwd(void);
void	minishell_unset(t_list **envp, char **params);
void	minishell_export(t_list **envp, char **params);

#endif

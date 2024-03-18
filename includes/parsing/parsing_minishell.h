/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:53:26 by acaffard          #+#    #+#             */
/*   Updated: 2024/03/18 09:46:24 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_MINISHELL_H
# define PARSING_MINISHELL_H

# include "../minishell.h"

void	parsing_cd(char **params);
void	parsing_pwd(char **params);
int		parsing_exit(char *params);
int		check_option(char **params);
void	parsing_echo(char **params);
void	parsing_unset(t_list **envp, char **params);
void	parsing_env(char **params, t_list *envp);
void	parsing_export(t_list **envp, char **params);

#endif

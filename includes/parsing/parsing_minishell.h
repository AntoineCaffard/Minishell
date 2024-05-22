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

int	parsing_cd(char **params);
int	parsing_exit(char **params);
int	check_option(char **params);
int	parsing_echo(char **params);
int	parsing_unset(t_list **envp, char **params);
int	parsing_env(char **params, t_list *envp);
int	parsing_export(t_list **envp, char **params);

#endif

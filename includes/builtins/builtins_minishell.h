/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_minishell.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:20:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/26 14:35:36 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_MINISHELL_H
# define BUILTINS_MINISHELL_H

# include "../minishell.h"

void	cd(char *path);
void	my_echo(char **params);
void	env(t_list *envp);
void	exit(void);
void	my_pwd(void);

#endif

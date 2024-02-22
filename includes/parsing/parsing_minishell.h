/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:53:26 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/22 11:16:29 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../LIBFT/libft.h"
# include "../minishell.h"

void	parsing_cd(char **params);
void	parsing_pwd(char **params);
void	parsing_env(char **params);
void	parsing_echo(char **params);
void	parsing_exit(char **params);
void	parsing_unset(char **params);
void	parsing_export(char **params);

#endif

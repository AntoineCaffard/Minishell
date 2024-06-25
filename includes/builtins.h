/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvondir <elvondir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:56:45 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/21 11:03:18 by elvondir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "LIBFT/libft.h"
# include "errors.h"

int	ft_add_new_node(t_list **list, char *value);
int	ft_print_export(t_list *list);

#endif

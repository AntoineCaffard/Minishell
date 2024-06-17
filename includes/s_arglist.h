/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_arglist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:37:54 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 16:01:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ARGLIST_H
# define S_ARGLIST_H
# include "LIBFT/libft.h"

typedef struct s_arglist
{
	char				*value;
	struct s_arglist	*next;
}	t_arglist;

void		ft_argdelone(t_arglist **args, void (*del)(void*));
t_arglist	*ft_arglast(t_arglist *lst);

#endif

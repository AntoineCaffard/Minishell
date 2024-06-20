/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_arglist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:37:54 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 08:57:37 by acaffard         ###   ########.fr       */
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

t_arglist	*ft_argnew(char *content);
t_arglist	*ft_arglast(t_arglist *lst);
t_arglist	*ft_argpop_two(t_arglist **head, t_arglist *node);
void		ft_argpush(t_arglist **list, t_arglist *to_push);
void		ft_argdelone(t_arglist **args, void (*del)(void*));
void		ft_argclear(t_arglist **list, void (*del)(void*));

#endif

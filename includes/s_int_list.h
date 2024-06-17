/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_int_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:36:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 13:46:53 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_INT_LIST_H
# define S_INT_LIST_H
# include "LIBFT/libft.h"

typedef struct s_int_list
{
	int					content;
	struct s_int_list	*next;
}	t_int_list;

t_int_list	*ft_int_lstnew(int content);
t_int_list	*ft_int_lstlast(t_int_list *lst);
size_t		ft_int_lstget_index(t_int_list *list, t_int_list *node);
int			ft_int_lstsize(t_int_list *lst);
void		ft_int_lstpush(t_int_list **lst, t_int_list *new_tail);
void		ft_int_lstpop_index(t_int_list **list, int index);
void		ft_int_lstclear(t_int_list **lst);

#endif

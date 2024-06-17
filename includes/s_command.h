/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:35:43 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 14:18:50 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_cmdlist_H
# define S_cmdlist_H
# include "LIBFT/libft.h"
# include "s_arglist.h"
# include "s_redlist.h"

typedef struct s_cmdlist
{
	t_arglist			*args;
	t_redlist			*redirs;
	struct s_cmdlist	*next;
}	t_cmdlist;

t_cmdlist	*ft_cmdnew(void);
t_cmdlist	*ft_cmdlast(t_cmdlist *lst);
void		ft_cmdpush(t_cmdlist **lst, t_cmdlist *to_push);

#endif

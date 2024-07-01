/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmdlist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:35:43 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 16:44:38 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_CMDLIST_H
# define S_CMDLIST_H
# include "LIBFT/libft.h"
# include "s_arglist.h"
# include "s_redlist.h"

typedef struct s_cmdlist
{
	t_arglist			*args;
	t_redlist			*redirs;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_cmdline
{
	int			error_code;
	int			return_value;
	t_cmdlist	*cmds;
}	t_cmdline;

t_cmdlist	*ft_cmdnew(void);
t_cmdlist	*ft_cmdlast(t_cmdlist *lst);
void		ft_cmdpush(t_cmdlist **lst, t_cmdlist *to_push);
void		ft_cmd_delone(t_cmdlist **list, void (*del)(void*));
void		ft_cmdclear(t_cmdlist **list, void (*del)(void*));
void		free_struct(t_cmdline	*line);
int			ft_cmdsize(t_cmdlist *lst);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_redlist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:26 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 09:23:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_REDLIST_H
# define S_REDLIST_H
# include "LIBFT/libft.h"

typedef enum e_redirection_type
{
	REDIRECTION_OUTFILE,
	REDIRECTION_INFILE,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC
}	t_redirection_type;

typedef struct s_redlist
{
	t_redirection_type		type;
	char					*link;
	struct s_redlist		*next;
}	t_redlist;

t_redlist	*ft_rednew(t_redirection_type type, char *link);
t_redlist	*t_redlast(t_redlist *lst);
void		ft_redpush(t_redlist **lst, t_redlist *to_push);
void		ft_red_delone(t_redlist **list, void (*del)(void*));
void		ft_redclear(t_redlist **list, void (*del)(void*));

#endif

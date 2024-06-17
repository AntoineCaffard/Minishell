/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_redirection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:26 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 14:17:46 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_REDIRECTION_H
# define S_REDIRECTION_H
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
	struct s_redlist	*next;
}	t_redlist;

#endif

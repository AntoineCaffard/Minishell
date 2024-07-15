/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rednew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:59:53 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/01 10:59:12 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_redlist.h"

t_redlist	*ft_rednew(t_redirection_type type, char *link)
{
	t_redlist	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redlist));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->next = NULL;
	new_redir->link = ft_strdup(link);
	if (new_redir->link)
		return (new_redir);
	free(new_redir);
	return (NULL);
}

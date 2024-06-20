/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:08 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 09:06:52 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_redlist.h"

t_redlist	*t_redlast(t_redlist *lst)
{
	if (!lst)
		return (NULL);
	if (!(lst->next))
		return (lst);
	return (t_redlist_get_last(lst->next));
}

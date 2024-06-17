/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:39:18 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 09:42:02 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_int_list.h"

t_int_list	*ft_int_lstnew(int content)
{
	t_int_list	*res;

	res = ft_calloc(1, sizeof(t_int_list));
	if (!res)
		return (NULL);
	res->content = content;
	return (res);
}

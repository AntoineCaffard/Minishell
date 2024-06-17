/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:14:03 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 14:15:26 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_argument.h"

t_argument	*ft_argnew(char *content)
{
	t_argument	*new_arg;

	new_arg = ft_calloc(1, sizeof(t_argument));
	if (!new_arg)
		return (NULL);
	new_arg->value = content;
	new_arg->next = NULL;
	return (new_arg);
}

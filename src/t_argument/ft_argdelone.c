/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:16:33 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/17 15:29:23 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/s_arglist.h"

void	ft_argdelone(t_arglist **args, void (*del)(void*))
{
	if (!args || !del || !*args)
		return ;
	del((*args)->value);
	free(*args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:50:13 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:40:09 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/errors.h"

size_t	print_error(int error_type)
{
	if (error_type == MALLOC_ERROR)
		ft_putstr_fd("Error : Allocation Error\n", 2);
	else if (error_type == EXPORT_ERROR)
		ft_putstr_fd("export : Not a valid identifier\n", 2);
	else if (error_type == TOO_MUCH_ARG_ERROR)
		ft_putstr_fd("Error : Too Many Arguments\n", 2);
	else if (error_type == PATH_ERROR)
		ft_putstr_fd("Error : Not a Directory\n", 2);
	else if (error_type == MISSING_HOME_ERROR)
		ft_putstr_fd("Error : Can't find HOME\n", 2);
	return (1);
}

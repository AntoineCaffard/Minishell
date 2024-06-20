/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:50:13 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/18 13:04:34 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/errors.h"

size_t	print_error(int error_type)
{
	if (error_type = MALLOC_ERROR)
		perror("Allocation Error\n");
	else if (error_type = EXPORT_ERROR)
		perror("export : Not a valid identifier");
	return (1);
}

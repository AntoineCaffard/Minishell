/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:50:13 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/24 16:10:25 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/errors.h"

size_t	print_error(int error_type)
{
	if (error_type == MALLOC_ERROR)
		perror("Error : Allocation Error\n");
	else if (error_type == EXPORT_ERROR)
		perror("export : Not a valid identifier\n");
	else if (error_type == TOO_MUCH_ARG_ERROR)
		perror("Error :Too Many Arguments\n");
	else if (error_type == PATH_ERROR)
		perror("Error ;Not a Directory\n");
		else if (error_type == MISSING_HOME_ERROR)
		perror("Error :Can't find HOME\n");
	return (1);
}

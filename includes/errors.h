/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:47:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:41:25 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include <stdio.h>
# include "LIBFT/libft.h"

typedef enum e_error
{
	NO_ERROR,
	MALLOC_ERROR,
	EXPORT_ERROR,
	TOO_MUCH_ARG_ERROR,
	PATH_ERROR,
	MISSING_HOME_ERROR,
}	t_error;

size_t	print_error(int error_type);

#endif

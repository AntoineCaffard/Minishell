/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:26:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/24 15:28:54 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	getcwd(pwd, 0);
	if (!pwd)
		return (print_error(MALLOC_ERROR));
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:01:25 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/26 09:45:44 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (!buffer)
		return ; // a revoir
	printf("%s\n", buffer);
	free(buffer);
}

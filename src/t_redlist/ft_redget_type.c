/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redget_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:11:44 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 15:11:58 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirection_type	get_type(t_arglist *arg)
{
	char	*str;

	str = arg->value;
	if (str[0] == '<')
	{
		if (!str[1])
			return (REDIRECTION_INFILE);
		return (REDIRECTION_HEREDOC);
	}
	if (!str[1])
		return (REDIRECTION_OUTFILE);
	return (REDIRECTION_APPEND);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:28:30 by trebours          #+#    #+#             */
/*   Updated: 2024/07/01 16:21:21 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_sigint(int signaux)
{
	(void)signaux;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	RETURN_VALUE = 130;
}

void	_sigint_exec(int signaux)
{
	(void)signaux;
	printf("\n");
	RETURN_VALUE = 130;
}

void	_sigintheredoc(int signaux)
{
	(void)signaux;
	printf("\n");
	RETURN_VALUE = 130;
}

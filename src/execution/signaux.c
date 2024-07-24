/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:28:30 by trebours          #+#    #+#             */
/*   Updated: 2024/07/17 11:02:07 by trebours         ###   ########.fr       */
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
	g_return_value = 130;
}

void	_sigint_exec(int signaux)
{
	(void)signaux;
	printf("\n");
	g_return_value = 130;
}

void	_sigintheredoc(int signaux)
{
	(void)signaux;
	printf("%c", 0);
	g_return_value = 130;
}

void	_signquit(int signaux)
{
	(void)signaux;
	printf("Quit\n");
}

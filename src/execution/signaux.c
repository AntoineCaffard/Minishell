/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:28:30 by trebours          #+#    #+#             */
/*   Updated: 2024/05/14 11:28:34 by trebours         ###   ########.fr       */
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
}

void	_sigint_exec(int signaux)
{
	(void)signaux;
	printf("\n");
	fflush(stdout);
}

void	_sigintheredoc(int signaux)
{
	(void)signaux;
	printf("Test\n");
}

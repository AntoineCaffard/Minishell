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

#include "../includes/minishell.h"

// static void    process(int sign_num)
// {
// 	if (!kill(getpid(), sign_num))
// 	{
// 		if (sign_num == SIGQUIT)
// 		{
// 			ft_putstr_fd("Quit: 3\n", 1);
// 			// g_status = 131;
// 		}
// 		else if (sign_num == SIGINT)
// 		{
// 			ft_putchar_fd('\n', 1);
// 			// g_status = 130;
// 		}
// 	}
// 	else if (sign_num == SIGINT)
// 	{
// 		ft_putchar_fd('\n', 1);
// 		// g_status = 1;
// 		// prompt();
// 	}
// }
//
// void        sigint_handler(int sign_num)
// {
// 	if ((sign_num == SIGINT || sign_num == SIGQUIT) && getpid() != 0)
// 		process(sign_num);
// 	else
// 	{
// 		if (sign_num == SIGINT)
// 		{
// 			ft_putchar_fd('\n', 1);
// 			// g_status = 1;
// 			// prompt();
// 		}
// 		else if (sign_num == SIGQUIT)
// 			ft_putstr_fd("\b\b  \b\b", 1);
// 	}
// }

void	_sigint(int signaux)
{
	(void)signaux;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
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

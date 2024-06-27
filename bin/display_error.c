/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:04:09 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 09:38:53 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_error_cmd(int cmd, char *prompt, char *file)
{
	if (cmd == 0)
		write(2, "Minishell: cd: ", 15);
	else if (cmd == 1)
		write(2, "\n", 1);
	else if (cmd == 2)
		write(2, "Minishell: env: ", 16);
	else if (cmd == 3)
		write(2, "Minishell: export: ", 19);
	else if (cmd == 4)
		write(2, "Minishell: exit: ", 17);
	else if (cmd == 5)
		write(2, "Minishell: unset: ", 18);
	if (file)
	{
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
	}
	if (prompt)
	{
		write (2, prompt, ft_strlen(prompt));
		write (2, "\n", 1);
	}
}

void	display_error(char *prompt, char *file_or_cmd)
{
	write(2, "Minishell: ", 11);
	if (file_or_cmd)
	{
		write(2, file_or_cmd, ft_strlen(file_or_cmd));
		write(2, ": ", 2);
		write(2, prompt, ft_strlen(prompt));
	}
	else
		write(2, prompt, ft_strlen(prompt));
	write(2, "\n", 1);
}

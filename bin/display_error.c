/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:04:09 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 08:41:39 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_error_cmd(int cmd, char *prompt, char *file)
{
		int	fd;
	int	fd_error;

	fd = dup(STDOUT_FILENO);
	fd_error = dup(STDERR_FILENO);
	dup2(fd_error, STDOUT_FILENO);
	close(fd_error);
	if (cmd == 0)
		printf("Minishell: cd: ");
	else if (cmd == 1)
		printf("\n");
	else if (cmd == 2)
		printf("Minishell: env: ");
	else if (cmd == 3)
		printf("Minishell: export: ");
	else if (cmd == 4)
		printf("exit\nMinishell: exit: ");
	else if (cmd == 5)
		printf("Minishell: unset: ");
	if (file)
		printf("%s: ", file);
	if (prompt)
		printf("%s\n", prompt);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	display_error(char *prompt, char *file_or_cmd)
{
	int	fd;
	int	fd_error;

	fd = dup(STDOUT_FILENO);
	fd_error = dup(STDERR_FILENO);
	dup2(fd_error, STDOUT_FILENO);
	close(fd_error);
	if (file_or_cmd)
		printf("%s: %s\n", file_or_cmd, prompt);
	else
		printf("%s\n", prompt);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

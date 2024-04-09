/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/09 14:20:26 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	(void) ac;
	(void) av;
	(void) envp;
	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		add_history(line);
		free (line);
	}
}

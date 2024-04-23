/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:53:41 by acaffard          #+#    #+#             */
/*   Updated: 2024/04/23 11:22:56 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_command_line pouet;
	char	*line;
	(void) ac;
	(void) av;
	(void) envp;
	// t_list envp
	while (1)
	{
		line = readline("Minishell V-2.0 : ");
		add_history(line);
		//pouet = create_command_line(line, envp);
		// if(pouet->error_code != NONE)
		// free line -> free pouet -> break;
		//executeur
		free (line);
	}
}

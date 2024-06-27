/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:52 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 18:18:19 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	main(int ac, char **av, char **envp) {
	t_cmdline cmdline;
	t_list *env;
	char *prompt;
	char *line;

	(void) ac;
	(void) av;
	cmdline.error_code = 0;
	cmdline.return_value = 0;
	cmdline.cmds = NULL;
	env = listify_str_array(envp);

	while (1) {
		prompt = ft_prompt(&cmdline);
		line = readline(prompt);
		ft_fill_cmdline(&cmdline, line);
		free(line);
		free(prompt);
		while (cmdline.cmds) {
			while (cmdline.cmds->args) {
				printf("%s ", cmdline.cmds->args->value);
				cmdline.cmds->args = cmdline.cmds->args->next;
			}
			printf("\n");
			while (cmdline.cmds->redirs) {
				printf("%s ", cmdline.cmds->redirs->link);
				cmdline.cmds->redirs = cmdline.cmds->redirs->next;
			}
			cmdline.cmds = cmdline.cmds->next;
		}
		ft_cmdclear(&(cmdline.cmds), free);
	}
	ft_lstclear(&env, free);
	return (0);
}

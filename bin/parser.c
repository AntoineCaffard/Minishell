/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:21:53 by antoine           #+#    #+#             */
/*   Updated: 2024/04/23 13:34:13 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_struct(t_command_line *res, char *line)
{
	int				i;
	bool			test_pipe;
	t_command		*command;

	i = 0;
	test_pipe = FALSE;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return ;
	while (line[i] && line[i] != '|')
		i++;
	if (line[i] == '|')
		test_pipe = TRUE;
	line[i] = '\0';
	command = create_command();
	if (!command)
		return ;
	t_command_add_back(&(res->commands), command);
	fill_command(command, ft_strdup(line));
	if (test_pipe)
		fill_struct(res, &(line[i + 1]));
}

int	fill_command(t_command *cmd, char *line)
{
	int	i;
	int	j;
	t_argument	*arg;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return 1;
	if (line[i] == '<'|| line[i] == '>')
	{
		if(line[i + 1] == '<'|| line[i + 1] == '>')
			j = 2;
		else
			j = 1;
		arg = create_argument(ft_strndup(&line[i], j));
		if (!arg)
			return 1;
		t_argument_add_back(&(cmd->args), arg);
		fill_command(cmd, &(line[i + j]));
		return 0;
	}
	j = 0;
	if (line[i] == '$')
		j++;
	while (line[i + j] && !is_separator(line[i + j]))
		j++;
	arg = create_argument(ft_strndup(&line[i], j));
	if (!arg)
		return 1;
	t_argument_add_back(&(cmd->args), arg);
	fill_command(cmd, &(line[i + j]));
	return (0);
}

int	main(void)
{
	t_command_line	test;
	char			*line;

	line = readline("TEST : ");
	test.commands = NULL;
	fill_struct(&test, line);
	while(test.commands)
	{
		while(test.commands->args)
		{
			printf("%s ", test.commands->args->value);
			test.commands->args = test.commands->args->next;
		}
		printf("\n");
		test.commands = test.commands->next;
	}
	return (0);
}

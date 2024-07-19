/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/19 10:17:18 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error_heredoc(char **res, char *new_line, int i)
{
	ft_putstr_fd(H_ERROR, 2);
	signal(SIGINT, _sigint);
	free(res[i]);
	free(new_line);
}

static int	loop(char **res, int i)
{
	char	*new_line;

	while (1)
	{
		new_line = readline("\033[1;33mheredoc: \033[0;m");
		if (g_return_value == 130)
		{
			ft_free_stringtab(res);
			free(new_line);
			return (g_return_value);
		}
		if (!new_line)
		{
			print_error_heredoc(res, new_line, i);
			break ;
		}
		if (!ft_strcmp(new_line, res[i]))
		{
			free(res[i]);
			free(new_line);
			break ;
		}
	}
	return (0);
}

int	all_heredoc(char *line, int error_index)
{
	char	**res;
	int		i;
	int		y;

	line[error_index] = '\0';
	res = init_heredoc(line);
	i = 0;
	y = 0;
	while (res[i])
	{
		signal(SIGINT, _sigintheredoc);
		y = loop(res, i);
		if (y > 0)
			return (y);
		i++;
	}
	free(res);
	free(line);
	creat_limiteur(NULL, 1);
	return (2);
}

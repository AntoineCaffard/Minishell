/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/17 09:54:18 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_heredoc(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<'
			&& (line[i + 1] && line[i + 2] != '<'))
		{
			i++;
			j++;
		}
		i++;
	}
	return (j);
}

static int	len(char *line)
{
	int	i;

	i = 0;
	while (ft_isalnum(line[i]))
		i++;
	return (i);
}

static char	*creat_limiteur(char *line, int y)
{
	static int	i = 0;
	char		*res;

	if (y)
	{
		i = 0;
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<'
			&& (line[i + 1] && (line[i + 2] != '<' && line[i + 2] != '>')))
		{
			i += 2;
			if (line[i] == ' ')
				i++;
			res = ft_strndup(&line[i], len(&line[i]));
			return (res);
		}
		i++;
	}
	return (NULL);
}

static char	**init_heredoc(char *line)
{
	char	**res;
	int		i;
	int		j;

	i = count_heredoc(line);
	res = ft_calloc(sizeof(char *), i + 1);
	j = 0;
	while (j < i)
	{
		res[j] = creat_limiteur(line, 0);
		j++;
	}
	return (res);
}

static int loop(char **res, int i)
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
			ft_putstr_fd(H_ERROR, 2);
			signal(SIGINT, _sigint);
			free(res[i]);
			free(new_line);
			break;
		}
		if (!ft_strcmp(new_line, res[i]))
		{
			free(res[i]);
			free(new_line);
			break;
		}
	}
	return (0);
}

int	all_heredoc(char *line, int error_index)
{
	char	**res;
	int		i;
	int 	y;

	line[error_index] = '\0';
	res = init_heredoc(line);
	i = 0;
	y = 0;
	signal(SIGINT, _sigintheredoc);
	while (res[i])
	{

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

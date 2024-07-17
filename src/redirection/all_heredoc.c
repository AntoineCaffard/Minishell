/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/16 07:17:58 by trebours         ###   ########.fr       */
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

static char	*creat_limiteur(char *line)
{
	static int	i = 0;
	char		*res;

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
		res[j] = creat_limiteur(line);
		j++;
	}
	return (res);
}

int	all_heredoc(char *line, int error_index)
{
	char	**res;
	char	*new_line;
	int		i;

	line[error_index] = '\0';
	res = init_heredoc(line);
	i = 0;
	signal(SIGINT, _sigintheredoc);
	while (res[i])
	{
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
				write(2, "minishell: warning: here-document at line 1 delimited by end-of-file\n", 70);
				signal(SIGINT, _sigint);
				free(res[i]);
				free(new_line);
				break ;
			}
			if (!ft_strcmp(new_line, res[i]))
			{
				free(res[i]);
				free(new_line);
				break ;
			}
		}
		i++;
	}
	free(res);
	free(line);
	return (2);
}

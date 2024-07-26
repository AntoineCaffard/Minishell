/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/26 08:27:18 by trebours         ###   ########.fr       */
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
			&& (line[i + 1] && line[i + 2] != '>' && line[i + 2] != '<'))
		{
			i++;
			j++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
			i += 2;
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

char	*creat_utils(char *line, int *i)
{
	char	*res;

	i[0] += 2;
	while (line[i[0]] == ' ')
		i[0]++;
	if (!line[i[0]])
		return (NULL);
	res = ft_strndup(&line[i[0]], len(&line[i[0]]));
	i += len(&line[i[0]]);
	if (!res)
		return (NULL);
	return (res);
}

char	*creat_limiteur(char *line, int y)
{
	static int	i;

	if (y)
	{
		i = 0;
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<'
			&& (line[i + 1] && (line[i + 2] != '<' && line[i + 2] != '>')))
			return (creat_utils(line, &i));
		i++;
	}
	return (NULL);
}

char	**init_heredoc(char *line)
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

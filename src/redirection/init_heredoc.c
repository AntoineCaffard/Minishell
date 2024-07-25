/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/25 14:51:36 by trebours         ###   ########.fr       */
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

char	*creat_limiteur(char *line, int y)
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
			while (line[i] == ' ')
				i++;
			if (!line[i])
				return (NULL);
			res = ft_strndup(&line[i], len(&line[i]));
			if (!res)
				return (NULL);
			return (res);
		}
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

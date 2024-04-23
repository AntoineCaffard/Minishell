/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:52:09 by trebours          #+#    #+#             */
/*   Updated: 2024/04/09 15:33:09 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_string_tab(char *line)
{
	int	rsl;
	int	i;

	i = 0;
	rsl = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i = i + 0;
		else if ((line[i] == '>' && line[i + 1] != '>') || (line[i] == '<'
			&& line[i + 1] != '<'))
			rsl++;
		else if ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>'))
		{
			rsl++;
			i++;
		}
		else
		{
			rsl++;
			while (line[i] && ft_isalnum(line[i+1]))
				i++;
		}
		i++;
	}
	return (rsl);
}

char	*ft_malloc(char *line)
{
	int		i;
	int		j;
	char	*rsl;

	j = 0;
	while (line[j] && ft_isalnum(line[j]))
		j++;
	rsl = calloc(sizeof(char), j + 1);
	i = 0;
	while (line[i] && ft_isalnum(line[i]))
	{
		rsl[i] = line[i];
		i++;
	}
	return (rsl);
}

char	*ft_charjoin(char const s1, char const *s2)
{
	size_t	total_length;
	size_t	i;
	size_t	j;
	char	*res;	

	if (!s1 || !s2)
		return (NULL);
	total_length = 1 + ft_strlen((char *)s2);
	res = (char *) ft_calloc(total_length + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (s1)
	{
		res[i] = ((char)s1);
		i++;
	}
	j = 0;
	while (s2 && ((char *)s2)[j])
	{
		res[i + j] = ((char *)s2)[j];
		j++;
	}
	return (res);
}

int	parseur(char *line, char **rsl)
{
	int	i;
	int	j;
	char *save;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i = i + 0;
		else if ((line[i] == '<' && line[i + 1] != '<')
			|| (line[i] == '>' && line[i + 1] != '>'))
			rsl[j++] = ft_charjoin(line[i], "");
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			rsl[j++] = ft_strjoin("<<", "");
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			rsl[j++] = ft_strjoin(">>", "");
			i++;
		}
		else if (line[i] != '"')
		{
			save = ft_malloc(&line[i + 1]);
			rsl[j++] = ft_charjoin(line[i], save);
			while (line[i] && ft_isalnum(line[i + 1]))
				i++;
			free(save);
		}
		i++;
	}
	return (0);
}

char	**main_parseur(char *line)
{
	char	**line_split;
	int		len;

	len = ft_string_tab(line);
	line_split = ft_calloc(sizeof(char *), len + 1);
	parseur(line, line_split);
	return (line_split);
}

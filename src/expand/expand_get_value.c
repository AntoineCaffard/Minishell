/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:38:29 by trebours          #+#    #+#             */
/*   Updated: 2024/07/16 05:55:36 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_cote(char *src)
{
	char	*tmp;
	char	*res;
	char	*c;
	int		i;

	if (!src)
		return (NULL);
	if (ft_charchr(src, 0) > -1)
	{
		i = ft_charchr(src, 0);
		if (src[i] == '"')
			c = ft_strdup("\'\0");
		else
			c = ft_strdup("\"\0");
	}
	else
		return (src);
	tmp = ft_strjoin(c, src);
	free(src);
	res = ft_strjoin(tmp, c);
	free(tmp);
	free(c);
	return (res);
}

char	*get_return_value(char **line, int j,
						char *first, t_cmdline *cmd_line)
{
	char	*end;
	char	*tmp;
	char	*res;

	end = ft_strdup(&line[0][j + 1]);
	tmp = ft_itoa(cmd_line->return_code);
	res = ft_strjoin(first, tmp);
	free(first);
	free(tmp);
	if (end)
	{
		tmp = ft_strjoin(res, end);
		free(end);
		free(res);
		free(line[0]);
		return (tmp);
	}
	free(line[0]);
	return (res);
}

char	*get_env_var(char **line, int j, char *first, char *var)
{
	char	*end;
	char	*tmp;
	char	*res;

	end = ft_strdup(&line[0][j]);
	if (var)
	{
		res = ft_strjoin(first, var);
		free(var);
	}
	else
		res = ft_strdup(first);
	free(first);
	if (end)
	{
		tmp = ft_strjoin(res, end);
		free(end);
		free(res);
		free(line[0]);
		return (tmp);
	}
	free(line[0]);
	return (res);
}

char	*get_value(t_list *list, char *param)
{
	while (list)
	{
		if (ft_strncmp(((char *)(list->content)), param,
			ft_env_var_len(param)) == 0)
		{
			if (((char *)(list->content))[ft_env_var_len(param)] == '=')
				return (list->content);
		}
		list = list->next;
	}
	return ("\0");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:33:09 by trebours          #+#    #+#             */
/*   Updated: 2024/05/28 13:54:05 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_verif_var(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

/*static size_t	ft_strlen_until_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}*/

char	*get_value(t_list *list, char *param)
{
	while (list)
	{
		if (ft_strncmp(((char *)(list->content)), param,
			ft_strlen_until_equal(param)) == 0)
		{
			if (((char *)(list->content))[ft_strlen_until_equal(param)] == '=')
				return (list->content);
		}
		list = list->next;
	}
	return ("\0");
}

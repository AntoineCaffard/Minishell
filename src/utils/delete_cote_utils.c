/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by trebours          #+#    #+#             */
/*   Updated: 2024/07/24 12:11:56 by acaffard         ###   ########.fr       */
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

int	verif_quote(char *value)
{
	int	len;

	if (!value)
		return (0);
	len = ft_strlen(value);
	if ((value[0] == '\"' || value[0] == '\'') && len == 1)
		return (1);
	else if (len == 2 && value[0] == '\"' && value[1] == '\"')
		return (1);
	else if (len == 2 && value[0] == '\'' && value[1] == '\'')
		return (1);
	return (0);
}

void	del_cote(t_arglist **args)
{
	free(args[0]->value);
	args[0]->value = ft_strdup(" ");
	args[0]->value[0] = 1;
}

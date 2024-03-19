/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:23:05 by trebours          #+#    #+#             */
/*   Updated: 2024/03/19 09:15:13 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_parsing(char **line)
{
	int	len;

	len = ft_stringtab_len(line);
	if (len == 1 || !ft_strncmp(line[len - 1], ">>", 3))
	{
		display_error("syntax error near unexpected token `newline\'", NULL);
		return (1);
	}
	return (0);
}

int	main_append(char **line, t_list *envp)
{
	if (ft_parsing(line))
		return (1);
	(void)envp;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:27:20 by trebours          #+#    #+#             */
/*   Updated: 2024/02/27 15:47:18 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parsing_readline(char *line, t_list **envp)
{
	char	**line_split;

	if (!line)
		return ;
	line_split = ft_split_str(line, " ");

	free(line);
	ft_start_minishell(line_split, envp);
	ft_free_stringtab(line_split);
}

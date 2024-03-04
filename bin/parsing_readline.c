/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:27:20 by trebours          #+#    #+#             */
/*   Updated: 2024/02/28 09:57:56 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int compare_string_to_character(char *line, char chr)
{
    int i;
	int	j;

    if (!line || !chr)
        return (0);
    i = 0;
	j = 0;
    while (line[i])
    {
        if (line[i] == chr)
            j++;
		i++;
	}
    return (j);
}

void	parsing_readline(char *line, t_list **envp)
{
	char	**line_split;

	if (!line)
		return ;
	if (compare_string_to_character(line, '|'))
	{
		main_pipe(line, envp[0]);
		return ;
	}
	line_split = ft_split_modif(line, ' ');
	ft_start_minishell(line_split, envp);
	ft_free_stringtab(line_split);
}

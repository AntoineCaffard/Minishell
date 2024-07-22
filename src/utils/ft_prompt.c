/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:22:01 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/19 15:59:03 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_prompt(t_cmdline *cmdline)
{
	char	*prompt;
	char	*save;
	char	**link;

	prompt = NULL;
	prompt = getcwd(prompt, 0);
	if (!prompt)
		return (NULL);
	if (!ft_strncmp(prompt, "/", 2))
		link = ft_split_str(prompt, " ");
	else
		link = ft_split_str(prompt, "/");
	free(prompt);
	prompt = NULL;
	if (!cmdline->return_code)
		prompt = ft_strjoin("\033[1;32m > minishell\033[0;m", ": (");
	else
		prompt = ft_strjoin("\033[1;31m > minishell\033[0;m", ": (");
	save = ft_strjoin(prompt, link[ft_stringtab_len(link) - 1]);
	free(prompt);
	prompt = ft_strjoin(save, ") \033[1;36m✗\033[0;m : ");
	ft_free_stringtab(link);
	free(save);
	return (prompt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:23:05 by trebours          #+#    #+#             */
/*   Updated: 2024/03/19 11:28:17 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_parsing(char **line)
{
	int	len;
	int	position2;
	int	position3;

	position2 = locate_string_in_stringtab(line, ">>", 2);
	position3 = locate_string_in_stringtab(line, ">>", 3);
	len = ft_stringtab_len(line);
	if (position2 == -1 && position3 == -1)
		return (1);
	if (position3 != -1 && position3 == len - 1)
	{
		display_error("syntax error near unexpected token `newline\'", NULL);
		return (1);
	}
	else if (position3 == -1 && position2 != -1 && line[position2][2] == '\0')
		return (1);
	return (0);
}

static int	execute(char **line, t_list *envp, int position, int fd)
{
	int	save;

	save = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!position && line[position][2] == '\0')
		ft_start_minishell(&line[2], &envp);
	else if (!position && line[position][2] != '\0')
		ft_start_minishell(&line[1], &envp);
	else
	{
		while (line[position])
		{
			free(line[position]);
			line[position] = NULL;
			position++;
		}
		ft_start_minishell(line, &envp);
	}
	dup2(save, STDOUT_FILENO);
	close(save);
	return (0);
}

static int	redirection_append(char **line, t_list *envp)
{
	int	position;
	int	fd;

	position = locate_string_in_stringtab(line, ">>", 2);
	if (line[position][2] != '\0')
		fd = open(&line[position][2], O_CREAT | O_APPEND |  O_WRONLY, 0644);
	else
		fd = open(line[position + 1], O_CREAT | O_APPEND |  O_WRONLY, 0744);
	if ((line[position][2] == '\0' && ft_stringtab_len(line) > 2)
		|| ((line[position][2] != '\0' && ft_stringtab_len(line) > 1)))
		return (execute(line, envp, position, fd));
	else
	{
		close(fd);
		return (0);
	}
	return (0);
}

int	main_append(char **line, t_list *envp)
{
	if (ft_parsing(line))
		return (1);
	if (redirection_append(line, envp))
		return (1);
	(void)envp;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Trebours <Trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:10:35 by Trebours          #+#    #+#             */
/*   Updated: 2024/04/15 13:21:10 by Trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_outfile(char *link, int i)
{
	int	fd;

	if (i == 1)
		fd = open(link, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (i == 2)
		fd = open(link, O_CREAT | O_APPEND | O_WRONLY, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_change_infile(char *link)
{
	int	fd;

	fd = open(link, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

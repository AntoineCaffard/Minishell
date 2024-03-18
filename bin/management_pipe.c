/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:41:28 by trebours          #+#    #+#             */
/*   Updated: 2024/03/18 09:10:01 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	management_fd(t_pipe *save_fd, int i)
{
	if (i == 0)
	{
		dup2(save_fd->save_first_fd[0], STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	}
	else if (i == save_fd->nmb_max_cmd - 1)
	{
		dup2(save_fd->save_fd, STDIN_FILENO);
		dup2(save_fd->save_first_fd[1], STDOUT_FILENO);
	}
	else if (i > 0)
	{
		dup2(save_fd->save_fd, STDIN_FILENO);
		dup2(save_fd->pipe[1], STDOUT_FILENO);
	}
	else if (i == -1)
	{
		dup2(save_fd->save_first_fd[0], STDIN_FILENO);
		dup2(save_fd->save_first_fd[1], STDOUT_FILENO);
	}
}

static void	management_pipe(char ***cmd, t_list *envp, t_pipe *save_fd)
{
	int	i;

	i = 0;
	while (i != save_fd->nmb_max_cmd)
	{
		if (pipe(save_fd->pipe))
			return ;
		management_fd(save_fd, i);
		ft_start_minishell(cmd[i], &envp);
		management_fd(save_fd, -1);
		if (save_fd->save_fd != -1)
			close(save_fd->save_fd);
		save_fd->save_fd = dup(save_fd->pipe[0]);
		close(save_fd->pipe[0]);
		close(save_fd->pipe[1]);
		ft_free_stringtab(cmd[i]);
		i++;
	}
}

static int	split_stringtab(char **str, char ***cmd, int nmb_of_ocurence)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (i != nmb_of_ocurence && y == 0)
	{
		cmd[i] = ft_split_modif(str[i], ' ');
		if (!cmd[i])
			y = 1;
		i++;
	}
	if (y == 1)
	{
		i--;
		while (i >= 0)
		{
			ft_free_stringtab(cmd[i]);
			i--;
		}
		free(cmd);
		return (1);
	}
	return (0);
}

static char	***ft_split_command(char *line, t_pipe *save_fd)
{
	char	**str;
	char	***cmd;
	int		nmb_of_ocurence;	

	str = ft_split_str(line, "|");
	if (!str)
		return (NULL);
	nmb_of_ocurence = ft_stringtab_len(str);
	cmd = ft_calloc(nmb_of_ocurence + 1, sizeof(char **));
	if (!cmd)
	{
		ft_free_stringtab(str);
		return (NULL);
	}
	if (split_stringtab(str, cmd, nmb_of_ocurence))
	{
		ft_free_stringtab(str);
		return (NULL);
	}
	ft_free_stringtab(str);
	save_fd->nmb_max_cmd = nmb_of_ocurence;
	return (cmd);
}

void	main_pipe(char *line, t_list *envp)
{
	t_pipe	struct_fd;
	char	***cmd;

	cmd = ft_split_command(line, &struct_fd);
	if (!cmd)
		return /* (1) */;
	struct_fd.save_first_fd[0] = dup(STDIN_FILENO);
	struct_fd.save_first_fd[1] = dup(STDOUT_FILENO);
	struct_fd.save_fd = -1;
	management_pipe(cmd, envp, &struct_fd);
	close(struct_fd.save_first_fd[1]);
	close(struct_fd.save_first_fd[0]);
	free(cmd);
}

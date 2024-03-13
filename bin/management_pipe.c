/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:41:28 by trebours          #+#    #+#             */
/*   Updated: 2024/03/04 09:41:28 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    management_fd(t_pipe *save_fd, int i)
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

void    management_pipe(char ***cmd, t_list *envp, t_pipe *save_fd, int nmb_cmd)
{
	int		i;
	// pid_t	tfork;

	i = 0;
	while (i != nmb_cmd)
	{
		if (pipe(save_fd->pipe))
		    return ;
		management_fd(save_fd, i);
		execute_command(cmd[i], envp);
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

void    main_pipe(char *line, t_list *envp)
{
    char    **str;
    char    ***cmd;
    int     nmb_of_ocurence;
    int     i;
    t_pipe  struct_fd;

    str = ft_split_str(line, "|");
    nmb_of_ocurence = ft_stringtab_len(str);
    cmd = ft_calloc(nmb_of_ocurence + 1, sizeof(char **));
    i = 0;
    while (i != nmb_of_ocurence)
    {
        cmd[i] = ft_split_modif(str[i], ' ');
        i++;
    }
    ft_free_stringtab(str);
    struct_fd.save_first_fd[0] = dup(STDIN_FILENO);
    struct_fd.save_first_fd[1] = dup(STDOUT_FILENO);
    struct_fd.nmb_max_cmd = nmb_of_ocurence;
    struct_fd.save_fd = -1;
    management_pipe(cmd, envp, &struct_fd, nmb_of_ocurence);
    close(struct_fd.save_first_fd[1]);
    close(struct_fd.save_first_fd[0]);
    free(cmd);
}

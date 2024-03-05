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
        dup2(0, STDIN_FILENO);
        dup2(1, STDOUT_FILENO);
    }
}

void    child_process(char **cmd, t_list *envp, t_pipe *save_fd, int nmb_cmd)
{
    char        **envp2;
    char  **path;

    path = init_path(envp);
    envp2 = init_t_list_in_stringtab(envp);
    cmd[0] = init_link(cmd[0], path);
    management_fd(save_fd, nmb_cmd);
    close(save_fd->pipe[0]);
    close(save_fd->pipe[1]);
    close(save_fd->save_first_fd[1]);
    close(save_fd->save_first_fd[0]);
    if (cmd[0])
        execve(cmd[0], cmd, envp2);
    ft_free_stringtab(cmd);
    perror("execve");
    exit(1);
}

void    management_pipe(char ***cmd, t_list *envp, t_pipe *save_fd, int nmb_cmd)
{
    int     i;
    pid_t   tfork;

    i = 0;
    while (i != nmb_cmd)
    {
        if (pipe(save_fd->pipe))
            return ;
        tfork = fork();
        if (tfork < 0)
            return ;
        if (tfork == 0)
            child_process(cmd[i], envp, save_fd, i);
        else
        {
            if (save_fd->save_fd != -1)
                close(save_fd->save_fd);
            save_fd->save_fd = dup(save_fd->pipe[0]);
            close(save_fd->pipe[0]);
            close(save_fd->pipe[1]);
            ft_free_stringtab(cmd[i]);
            management_fd(save_fd, -1);
            while (waitpid(-1, NULL, 0) != -1)
			    continue ;
        }
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

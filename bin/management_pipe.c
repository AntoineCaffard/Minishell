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

void    management_pipe(char ***cmd, t_list *envp, t_pipe *save_fd, int nmb_cmd)
{
    int i;

    i = 0;
    while (i != nmb_cmd)
    {
        if (pipe(save_fd->pipe))
            return ;
        save_fd->tfork = fork();
        if (!save_fd->tfork)
            return (0);
        
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
    struct_fd.save_first_fd[0] = dup(STDIN_FILENO);
    struct_fd.save_first_fd[1] = dup(STDOUT_FILENO);
    management_pipe(cmd, envp, &struct_fd, nmb_of_ocurence);
}

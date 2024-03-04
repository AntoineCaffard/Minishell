/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:04:09 by trebours          #+#    #+#             */
/*   Updated: 2024/03/01 09:20:58 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    display_error(int cmd, char *prompt, char *file)
{
    dup2(2, STDOUT_FILENO);
    if (cmd == 0)
        printf("Minishell: cd: ");
    else if (cmd == 1)
        printf("\n");
    else if (cmd == 2)
        printf("Minishell: env: ");
    else if (cmd == 3)
        printf("Minishell: export: ");
    else if (cmd == 4)
        printf("exit\nMinishell: exit: ");
    else if (cmd == 5)
        printf("Minishell: unset: ");
    if (file)
        printf("%s: ", file);
    if (prompt)
        printf("%s\n", prompt);
    dup2(1, STDOUT_FILENO);
}

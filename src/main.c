/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:52 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 13:49:24 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/s_int_list.h"
#include "../includes/minishell.h"
#include <stdio.h>

static t_list *create_env_list(char **envp)
{
	int		i;
	t_list  *new = NULL;

	i = 0;
	while (envp[i])
	{
		ft_add_new_node(&new, envp[i]);
		i++;
	}
	return (new);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	t_list	*env = create_env_list(envp);
	//ft_export(&env, &(av[1]));
    ft_pwd();
    ft_cd(&env, &(av[1]));
	ft_export(&env, NULL);
    ft_pwd();
	ft_lstclear(&env, free);
	return (0);
}

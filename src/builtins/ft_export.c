/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvondir <elvondir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:57:14 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/21 11:03:39 by elvondir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"


static bool	check_validity(char *string)
{
	size_t	iterator;

	if (!string)
		return (false);
	iterator = 0;
	while (string[iterator] && ft_isalpha(string[iterator]))
		iterator++;
	if (string[iterator] && string[iterator] == '+')
		iterator++;
	if (string[iterator] && string[iterator] != '=')
		return (false);
	return (true);
}

static size_t	export_loop(t_list **envp, char *argument)
{
	bool	checker;

	checker = check_validity(argument);
	if (checker == false)
		return (print_error(EXPORT_ERROR));
	if (!*envp)
		return (add_new_env_var(envp, argument));
	return (0);
	//export()
}

int	ft_export(t_list **envp, char **arguments)
{
	size_t	iterator;
	size_t	nb_error;

	if (ft_stringtab_len(arguments) == 0)
		return (ft_print_export(*envp));
	iterator = 0;
	nb_error = 0;
	while (arguments[iterator])
	{
		nb_error += init_export_loop(envp, arguments[iterator]);
		iterator++;
	}
	if (nb_error)
		return (1);
	return (0);
}

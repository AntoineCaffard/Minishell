/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvondir <elvondir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 10:57:14 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/15 09:15:02 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static bool	check_validity(char *string)
{
	size_t	iterator;

	if (!string)
		return (false);
	if (ft_isdigit(string[0]))
		return (false);
	iterator = 0;
	while (string[iterator]
		&& (ft_isalnum(string[iterator]) || string[iterator] == '_'))
		iterator++;
	if (string[iterator] && string[iterator] == '+' && string[iterator + 1])
		iterator++;
	if (string[iterator] && string[iterator] != '=')
		return (false);
	return (true);
}

static int	export(t_list **envp, char *argument)
{
	size_t	var_len;

	var_len = ft_env_var_len(argument);
	if (argument[var_len] == '+')
		return (ft_append_node(envp, argument));
	return (update_env_var(envp, argument));
}

static size_t	init_export_loop(t_list **envp, char *argument)
{
	bool	checker;

	checker = check_validity(argument);
	if (checker == false)
		return (print_error(EXPORT_ERROR));
	if (!*envp)
		return (ft_add_new_node(envp, argument));
	return (export(envp, argument));
}

int	ft_export(t_list **envp, char **arguments)
{
	size_t	iterator;
	size_t	nb_error;

	if (ft_stringtab_len(arguments) == 0)
		return (ft_print_sorted_env(*envp));
	iterator = 0;
	nb_error = 0;
	while (arguments[iterator])
	{
		nb_error += init_export_loop(envp, arguments[iterator]);
		iterator++;
	}
	if (nb_error > 0)
		return (1);
	return (0);
}

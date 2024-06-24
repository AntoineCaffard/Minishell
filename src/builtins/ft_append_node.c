/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:01:15 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/24 13:52:48 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static char	*remove_plus_env_var(char *env_var)
{
	char	*tmp;
	size_t	var_len;

	var_len = ft_env_var_len(env_var);
	env_var[var_len] = '\0';
	tmp = ft_strjoin(env_var, &(env_var)[var_len + 1]);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static int	create_node_append(t_list **envp, char *argument)
{
	int error;

	argument = remove_plus_env_var(argument);
	if (!argument)
		return(print_error(MALLOC_ERROR));
	error = ft_add_new_node(envp, argument);
	free(argument);
	return (error);
}

static int	append_env_var(t_list *env_var, char *value)
{
	size_t	var_len;
	char	*tmp;

	var_len = ft_env_var_len(value);
	if (!value[var_len])
		return (0);
	if (((char *) env_var->content)[var_len] == '\0')
		tmp = ft_strjoin(env_var->content, &value[var_len + 1]);
	else
		tmp = ft_strjoin(env_var->content, &value[var_len + 2]);
	if (!tmp)
		return (print_error(MALLOC_ERROR));
	free(env_var->content);
	env_var->content = tmp;
	return (0);
}

int	ft_append_node(t_list **envp, char *argument)
{
	size_t	var_len;
	t_list	*to_append;

	var_len = ft_env_var_len(argument);
	to_append = ft_get_env_node(*envp, argument, var_len);
	if (!to_append)
		return (create_node_append(envp, argument));
	return (append_env_var(to_append, argument));
}

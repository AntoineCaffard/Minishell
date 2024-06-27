/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:23 by acaffard          #+#    #+#             */
/*   Updated: 2024/06/27 14:39:17 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	manage_no_args(t_list **envp)
{
	t_list	*node;

	node = ft_get_env_node(*envp, "HOME", 4);
	if (!node)
		return (print_error(MISSING_HOME_ERROR));
	return (switch_directory(&(((char *) node->content)[5]), envp));
}

static int	update_pwds(t_list **envp, char *old_pwd, char *new_pwd)
{
	char	*buffer;
	int		error;

	error = 0;
	buffer = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (!buffer)
		return (MALLOC_ERROR);
	error += update_env_var(envp, buffer);
	free(buffer);
	buffer = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	if (!buffer)
		return (MALLOC_ERROR);
	error += update_env_var(envp, buffer);
	free(buffer);
	if (error > 0)
		return (1);
	return (0);
}

int	switch_directory(char *path, t_list **envp)
{
	int		status;
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = NULL;
	new_pwd = NULL;
	if (path[0] == '~' && !path[1])
		return (manage_no_args(envp));
	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (print_error(MALLOC_ERROR));
	status = chdir(path);
	if (status != 0)
	{
		free(old_pwd);
		return (print_error(PATH_ERROR));
	}
	new_pwd = getcwd(new_pwd, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		return (print_error(MALLOC_ERROR));
	}
	return (update_pwds(envp, old_pwd, new_pwd));
}

int	ft_cd(t_list **envp, char **arguments)
{
	if (ft_stringtab_len(arguments) > 1)
		return (print_error(TOO_MUCH_ARG_ERROR));
	if (ft_stringtab_len(arguments) == 0)
		return (manage_no_args(envp));
	return (switch_directory(*arguments, envp));
}

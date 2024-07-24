/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:52 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/24 06:09:34 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_return_value = 0;

void	minishell_exec(t_cmdline *command_line, t_list *envp)
{
	t_cmdline	cmd_buffer;

	cmd_buffer = *command_line;
	main_expand(&cmd_buffer, &envp);
	cmd_buffer = *command_line;
//	if (ft_verif_exit(&cmd_buffer, &envp))
		main_pipe(&cmd_buffer, &envp);
	command_line->return_code = cmd_buffer.return_code;
}

int	loop_main(t_cmdline *command_line, t_list *env, char *line)
{
	if (!env)
		return (1);
	while (1)
	{
		free_struct(command_line);
		line = manage_line(command_line, env);
		if (g_return_value)
			command_line->return_code = g_return_value;
		if (!line)
			continue ;
		command_line->error_code = 0;
		add_history(line);
		if (verif_lexer(line, command_line))
			continue ;
		parse_minishell(command_line, line, env);
		if (command_line->error_code)
			command_line->return_code = command_line->error_code;
		else
			minishell_exec(command_line, env);
		g_return_value = 0;
	}
}

static t_list	*init_env_if_null(void)
{
	t_list	*res;
	char	*pwd;

	pwd = ft_strdup("42");
	if (!pwd)
		return (NULL);
	res = ft_lstnew(pwd);
	if (!res)
		return (NULL);
	return (res);
}

static t_list	*init_env(char **envp)
{
	t_list	*env;
	t_list	*tmp;

	if (envp[0] != NULL)
	{
		env = listify_str_array(envp);
		if (!env)
			return (NULL);
		tmp = init_env_if_null();
		if (!tmp)
		{
			ft_lstclear(&env, free);
			return (NULL);
		}
		ft_lstadd_front(&env, tmp);
		return (env);
	}
	env = init_env_if_null();
	if (!env)
		return (NULL);
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	t_cmdline		command_line;
	t_list			*env;
	char			*line;
	int				i;

	(void) ac;
	(void) av;
	i = 0;
	signal(SIGINT, _sigint);
	signal(SIGQUIT, SIG_IGN);
	env = init_env(envp);
	if (!env)
		return (print_error(MALLOC_ERROR));
	command_line.cmds = NULL;
	command_line.error_code = 0;
	command_line.return_code = 0;
	line = NULL;
	i = loop_main(&command_line, env, line);
	free_struct(&command_line);
	ft_lstclear(&env, free);
	rl_clear_history();
	return (i);
}

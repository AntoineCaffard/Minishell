/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:12:21 by trebours          #+#    #+#             */
/*   Updated: 2024/02/27 15:34:41 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_prompt(void)
{
	char	*prompt = NULL;
	char	*save = save;
	char	**link;

	prompt = getcwd(prompt, 0);
	link = ft_split_str(prompt, "/");
	prompt = NULL;
	prompt = ft_strjoin("\033[6;32m > minishell\033[0;m", ": (");
	save = ft_strjoin(prompt, link[ft_stringtab_len(link) - 1]);
	free(prompt);
	prompt = ft_strjoin(save, ") \033[1;36m✗\033[0;m ");
	ft_free_stringtab(link);
	free(save);
	return (prompt);
}

void	ft_start_minishell(char **line, t_list **envp)
{
	if (!line)
		return ;
	if (ft_strncmp(line[0], "echo", ft_strlen(line[0])))
		minishell_echo(&line[1]);
	else if (ft_strncmp(line[0], "cd", ft_strlen(line[0])))
		minishell_cd(line[1]);
	else if (ft_strncmp(line[0], "env", ft_strlen(line[0])))
		minishell_env(*envp);
	else if (ft_strncmp(line[0], "export", ft_strlen(line[0])))
		minishell_export(*envp, &line[1]);
	else if (ft_strncmp(line[0], "pwd", ft_strlen(line[0])))
		minishell_pwd();
	else if (ft_strncmp(line[0], "unset", ft_strlen(line[0])))
		minishell_unset(*envp, &line[1]);
	else
		execute_command(line, &envp[0]);
}

void	minishell(t_list *envp)
{
	char *line;
	char *prompt = NULL;
	(void)envp;

	while (1)
	{
		prompt = ft_prompt();
		line = readline(prompt);
		free(prompt);
		if (ft_strncmp(line[0], "exit ", 5))
		{
			if (minishell_exit(line))
				break ;
		}
		add_history(line);
		parsing_readline(line);			
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_list	*t_list_envp;

	t_list_envp = init_stringtab_in_t_list(envp);
	minishell(t_list_envp);
	ft_lstclear(&t_list_envp, free);
}

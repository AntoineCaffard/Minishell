/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:12:21 by trebours          #+#    #+#             */
/*   Updated: 2024/03/19 09:14:35 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_prompt(void)
{
	char	*prompt;
	char	*save;
	char	**link;

	prompt = NULL;
	prompt = getcwd(prompt, 0);
	link = ft_split_str(prompt, "/");
	free(prompt);
	prompt = NULL;
	prompt = ft_strjoin("\033[1;32m > minishell\033[0;m", ": (");
	save = ft_strjoin(prompt, link[ft_stringtab_len(link) - 1]);
	free(prompt);
	prompt = ft_strjoin(save, ") \033[1;36m✗\033[0;m ");
	ft_free_stringtab(link);
	free(save);
	return (prompt);
}

void	ft_start_minishell(char **line, t_list **envp)
{
	int	len;

	len = ft_stringtab_len(line);
	if (!line)
		return ;
	else if (locate_string_in_stringtab(line, ">>") != -1)
		main_append(line, *envp);
	else if (strncmp(line[0], "<<", 2) == 0)
		heredoc(line, envp);
	else if (!ft_strncmp(line[0], "echo", 5) || !ft_strncmp(line[0], "echo ", 5))
		parsing_echo(&line[1]);
	else if (!ft_strncmp(line[0], "cd", 3) || !ft_strncmp(line[0], "cd ", 3))
		parsing_cd(&line[1]);
	else if (!ft_strncmp(line[0], "env", 4) || !ft_strncmp(line[0], "env ", 4))
		parsing_env(&line[1], *envp);
	else if (!ft_strncmp(line[0], "export", 7)
		|| !ft_strncmp(line[0], "export ", 7))
		parsing_export(envp, &line[1]);
	else if (!ft_strncmp(line[0], "pwd", 4) || !ft_strncmp(line[0], "pwd ", 4))
		minishell_pwd();
	else if (!ft_strncmp(line[0], "unset", 6)
		|| !ft_strncmp(line[0], "unset ", 6))
		minishell_unset(envp, &line[1]);
	else if (len > 2 && (!strncmp(line[0], "<", ft_strlen(line[0]))
			|| !strncmp(line[len - 2], ">", ft_strlen(line[len - 2]))))
		main_redirection(line, *envp);
	else
		execute_command(line, *envp);
}

void	minishell(t_list *envp)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = ft_prompt();
		line = readline(prompt);
		free(prompt);
		if (ft_strncmp(line, "", ft_strlen(line)))
		{
			add_history(line);
			if ((!ft_strncmp(line, "exit", 5) || !ft_strncmp(line, "exit ", 5)))
			{
				if (parsing_exit(line))
				{
					free(line);
					break ;
				}
			}
			else
				parsing_readline(line, &envp);
		}
		free(line);
	}
	clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*t_list_envp;

	(void)argc;
	(void)argv;
	t_list_envp = init_stringtab_in_t_list(envp);
	minishell(t_list_envp);
	ft_lstclear(&t_list_envp, free);
	return (0);
}

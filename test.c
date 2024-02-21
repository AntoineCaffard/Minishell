/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:27:24 by trebours          #+#    #+#             */
/*   Updated: 2024/02/21 14:02:09 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif(char *src, char *cmd)
{
	int	i;

	i = 0;
	if (!src || !cmd)
		exit(1);
	while (cmd[i] && src[i])
	{
		if (src[i] != cmd[i])
			return (0);
		i++;
	}
	if (!src[i] && !cmd[i])
		return (1);
	return (0);
}

void	ft_free(char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		free(src[i]);
		i++;
	}
	free(src);
}

int main(void)
{
	char	*ligne = NULL;
	char	buffer[4096];
	char	**rsl;

	rl_clear_history();
	while (1)
	{
		ligne = readline("\033[1;32m➜ minishell \033[1;37m");
		rsl = ft_split_modif(ligne, ' ');
		if (ft_verif(rsl[0], "exit"))
			return (0);
		else if (ft_verif(rsl[0], "pwd"))
		{
			getcwd(buffer , sizeof(buffer));
			printf("%s\n", buffer);
		}
		else if (ft_verif(rsl[0], "cd"))
			chdir(rsl[1]);
		else if (ft_verif(rsl[0], "echo"))
		{
			if (ft_verif(rsl[1], "-n"))
			{
				printf("%s", rsl[2]);
				// if (rsl[1][ft_strlen(rsl[1]) - 1] != '\n')
				// {
				// 	printf("\033[1;47m");
				// 	printf("\033[2;30m%%\n\033[0;37m");
				// }
			}
			else
			{
				printf("%s", rsl[1]);
				if (rsl[1][ft_strlen(rsl[1]) - 1] != '\n')
					printf("\n");
			}
		}
		ft_free(rsl);
	}
	return(0);
}

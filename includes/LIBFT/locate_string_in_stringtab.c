/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_string_in_stringtab.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trebours <trebours@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:52:01 by trebours          #+#    #+#             */
/*   Updated: 2024/03/19 10:46:26 by trebours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	locate_string_in_stringtab(char **stringtab, char *string, int len_check)
{
	int	i;

	if (!stringtab || !string)
		return (-1);
	i = 0;
	while (stringtab[i])
	{
		if (len_check && !ft_strncmp(stringtab[i], string, len_check))
			return (i);
		else if (!len_check && !ft_strncmp(stringtab[i],
				string, ft_strlen(stringtab[i])))
			return (i);
		i++;
	}
	return (-1);
}

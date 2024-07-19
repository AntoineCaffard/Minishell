/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by acaffard          #+#    #+#             */
/*   Updated: 2024/07/19 11:14:53 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_alnum(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	has_quotes(char *string)
{
	while (*string)
	{
		if ((*string == '\'') | (*string == '\"'))
			return (1);
		string++;
	}
	return (0);
}

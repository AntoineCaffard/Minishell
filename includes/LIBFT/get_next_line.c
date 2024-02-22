/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:10:07 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:05:51 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fusion(char *left, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(left, buffer);
	free(left);
	return (tmp);
}

static char	*read_line(int fd, char *left)
{
	char	*buffer;
	int		read_value;

	if (!left)
		left = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || !left)
		return (NULL);
	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value == -1)
		{
			free (left);
			free (buffer);
			return (NULL);
		}
		buffer[read_value] = 0;
		left = ft_fusion(left, buffer);
		if (ft_strchr(left, '\n'))
			break ;
	}
	free (buffer);
	return (left);
}

static char	*get_line(char *left)
{
	int		i;
	char	*str;

	i = 0;
	if (!left[i])
		return (NULL);
	while (left[i] && left[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (left[i] && left[i] != '\n')
	{
		str[i] = left[i];
		i++;
	}
	if (left[i] && left[i] == '\n')
		str[i++] = '\n';
	return (str);
}

static char	*get_left(char *left)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (left[i] && left[i] != '\n')
		i++;
	if (!left[i])
	{
		free (left);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(left) - i + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (left[++i])
		str[j++] = left[i];
	str[j] = '\0';
	free (left);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*left;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	left = read_line(fd, left);
	if (!left)
		return (NULL);
	result = get_line(left);
	left = get_left(left);
	return (result);
}

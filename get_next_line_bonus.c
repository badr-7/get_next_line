/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:39:19 by mel-hous          #+#    #+#             */
/*   Updated: 2021/12/11 10:28:03 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"get_next_line_bonus.h"

char	*ft_clear_result(char *result)
{
	int		i;
	int		j;
	char	*new_result;

	i = 0;
	j = 0;
	while (result[i] != '\0' && result[i] != '\n')
		i++;
	if (result[i] == '\n')
		i++;
	if (result[i] == 0)
	{
		free (result);
		return (NULL);
	}
	new_result = (char *)malloc(sizeof(char) * (ft_strlen(result) - i + 1));
	if (!new_result)
		return (NULL);
	while (result[i] != '\0')
		new_result[j++] = result[i++];
	new_result[j] = 0;
	free(result);
	return (new_result);
}

char	*ft_new_line(char *result)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (result[0] == '\0')
		return (NULL);
	while (result[i] != '\0' && result[i] != '\n')
		i++;
	if (result[i] == '\n')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	while (j < i)
	{
		dest[j] = result[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

char	*ft_read(int fd, char *result)
{
	char	*dest;
	int		res;

	dest = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!dest)
		return (NULL);
	res = 1;
	while (res)
	{
		res = read(fd, dest, BUFFER_SIZE);
		if (res == -1)
		{
			free (dest);
			return (NULL);
		}
		dest[res] = 0;
		result = ft_strjoin(result, dest);
		if (ft_strchr(dest, '\n') != NULL || res == 0)
			break ;
	}
	free (dest);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result[65535];
	char		*dest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result[fd] = ft_read(fd, result[fd]);
	if (result[fd] == NULL)
		return (NULL);
	dest = ft_new_line(result[fd]);
	result[fd] = ft_clear_result(result[fd]);
	return (dest);
}

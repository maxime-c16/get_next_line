/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:53:17 by mcauchy           #+#    #+#             */
/*   Updated: 2025/02/14 17:38:25 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *str, int start, int len)
{
	char	*substr;
	int		i;

	if (!str || !*str)
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && str[start + i])
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*read_line(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && has_newline(line) < 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read == 0 && !line))
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(line, buffer);
		free(line);
		line = ft_strdup(temp);
		free(temp);
	}
	if (bytes_read == 0 && !line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*str;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	str = ft_substr(line, 0, has_newline(line) + 1);
	if (!str && line && line[0] != '\0')
	{
		str = ft_strdup(line);
		free(line);
	}
	else
	{
		temp = ft_strdup(line + has_newline(line) + 1);
		free(line);
		line = ft_strdup(temp);
		free(temp);
	}
	return (str);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

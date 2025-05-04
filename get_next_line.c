/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:53:17 by mcauchy           #+#    #+#             */
/*   Updated: 2025/05/04 14:35:04 by mecauchy         ###   ########.fr       */
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
	while (bytes_read > 0 && has_newline(line) < 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(line, buffer);
		free(line);
		line = temp;
	}
	return (line);
}

static char	*extract_line(char **line)
{
	char	*str;
	char	*temp;
	int		nl_index;

	nl_index = has_newline(*line);
	if (nl_index >= 0)
	{
		str = ft_substr(*line, 0, nl_index + 1);
		temp = ft_substr(*line, nl_index + 1, ft_strlen(*line) - nl_index - 1);
		free(*line);
		*line = temp;
	}
	else
	{
		str = ft_strdup(*line);
		free(*line);
		*line = NULL;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (!line || line[0] == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (extract_line(&line));
}

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*line;

// 	if (ac != 2)
// 		return (1);
// 	fd = open(av[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }

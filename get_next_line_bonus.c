/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:56:30 by mecauchy          #+#    #+#             */
/*   Updated: 2025/05/04 16:44:30 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
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

char	*get_next_line(int fd)
{
	t_node	*node;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(fd);
	if (!node)
		return (NULL);
	node->buff = read_line(fd, node->buff);
	if (!node->buff)
	{
		remove_node(fd);
		return (NULL);
	}
	if (node->buff[0] == '\0')
	{
		remove_node(fd);
		return (NULL);
	}
	line = extract_line(&node->buff);
	if (!node->buff)
		remove_node(fd);
	return (line);
}

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	int		fd2;
// 	int		fd3;
// 	char	*line;
// 	char	*line2;
// 	char	*line3;

// 	fd = open(av[1], O_RDONLY);
// 	fd2 = open(av[2], O_RDONLY);
// 	fd3 = open(av[3], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
// 	while (line || line2 || line3)
// 	{
// 		if (line)
// 			printf("(fd 1) %s", line);
// 		if (line2)
// 			printf("(fd 2) %s", line2);
// 		if (line3)
// 			printf("(fd 3) %s", line3);
// 		free(line);
// 		free(line2);
// 		free(line3);
// 		line = get_next_line(fd);
// 		line2 = get_next_line(fd2);
// 		line3 = get_next_line(fd3);
// 	}
// 	close(fd);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }

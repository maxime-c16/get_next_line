/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:21:27 by mecauchy          #+#    #+#             */
/*   Updated: 2025/05/04 14:38:19 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_gnl	*_gnl(void)
{
	static t_gnl	gnl;

	return (&gnl);
}

int	has_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
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

t_node	*get_node(int fd)
{
	t_gnl	*g;
	t_node	*gnl;

	g = _gnl();
	gnl = g->head;
	while (gnl)
	{
		if (gnl->fd == fd)
			return (gnl);
		gnl = gnl->next;
	}
	gnl = malloc(sizeof(t_node));
	if (!gnl)
		return (NULL);
	gnl->fd = fd;
	gnl->buff = ft_strdup("");
	if (!gnl->buff)
		return (NULL);
	gnl->next = g->head;
	g->head = gnl;
	return (gnl);
}

void	remove_node(int fd)
{
	t_gnl	*g;
	t_node	**prev;
	t_node	*to_free;

	g = _gnl();
	to_free = NULL;
	prev = &g->head;
	while (*prev)
	{
		if ((*prev)->fd == fd)
		{
			to_free = *prev;
			*prev = to_free->next;
			free(to_free->buff);
			free(to_free);
			return ;
		}
		prev = &((*prev)->next);
	}
}

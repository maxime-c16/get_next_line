/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:35:40 by mecauchy          #+#    #+#             */
/*   Updated: 2025/05/04 14:48:33 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_node
{
	int				fd;
	char			*buff;
	struct s_node	*next;
}				t_node;

typedef struct s_gnl
{
	struct s_node	*head;
}				t_gnl;

char	*ft_substr(char *str, int start, int len);
void	remove_node(int fd);
t_node	*get_node(int fd);
int		has_newline(char *str);
char	*ft_strdup(char *str);
int		ft_strlen(char *s);

#endif
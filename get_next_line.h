/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:30:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/01/05 16:16:49 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*buf;
	struct s_list	*next;
}					t_list;
size_t				ft_strlen(const char *s);
char				*ft_strchr(char *s, char c);
char				*ft_ssubstr(char *start, char *end);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_strjoin(char *s1, char *s2);
char				*get_next_line(int fd);
t_list				*get_node(int fd, t_list **tmp);
char				*set_buf(t_list **fdl, int fd, char *nextbuf);
void				ft_lstclear(t_list **lst);
void				free_node(int fd, t_list **fdl);
char				*get_total(int fd, t_list *fdl);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:30:51 by seojepar          #+#    #+#             */
/*   Updated: 2024/01/05 16:17:01 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_node(int fd, t_list **tmp)
{
	t_list	*new;
	t_list	*it;

	it = *tmp;
	while (it)
	{
		if (it->fd == fd)
			return (it);
		it = it->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!new->buf)
	{
		free(new);
		return (NULL);
	}
	new->buf[0] = '\0';
	new->next = *tmp;
	*tmp = new;
	return (new);
}

char	*set_buf(t_list **fdl, int fd, char *nextbuf)
{
	t_list	*tmp;

	tmp = *fdl;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			tmp->buf = malloc(ft_strlen(nextbuf) + 1);
			if (!tmp->buf)
				return (NULL);
			ft_memmove(tmp->buf, nextbuf, ft_strlen(nextbuf) + 1);
			return (tmp->buf);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_total(int fd, t_list *fdl)
{
	int		i;
	char	*total;
	char	buf[BUFFER_SIZE + 1];

	total = get_node(fd, &fdl)->buf;
	i = 0;
	while (i <= BUFFER_SIZE)
		buf[i++] = '\0';
	while (i)
	{
		total = ft_strjoin(total, buf);
		if (ft_strchr(total, '\n'))
			return (total);
		i = read(fd, buf, BUFFER_SIZE);
	}
	return (total);
}

char	*get_next_line(int fd)
{
	static t_list	*fdl = NULL;
	char			*total;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0 || !get_node(fd, &fdl))
	{
		if (get_node(fd, &fdl))
			free(get_node(fd, &fdl)->buf);
		free_node(fd, &fdl);
		return (NULL);
	}
	total = get_total(fd, fdl);
	if (ft_strchr(total, '\n'))
	{
		set_buf(&fdl, fd, ft_strchr(total, '\n') + 1);
		return (ft_ssubstr(total, ft_strchr(total, '\n')));
	}
	if (*total == '\0')
	{
		free(total);
		free_node(fd, &fdl);
		return (NULL);
	}
	free_node(fd, &fdl);
	return (total);
}

void	free_node(int fd, t_list **fdl)
{
	t_list	*tmp;
	t_list	*before;

	before = NULL;
	tmp = *fdl;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			if (before)
			{
				before->next = tmp->next;
				free(tmp);
				return ;
			}
			tmp = (*fdl)->next;
			free(*fdl);
			*fdl = tmp;
			return ;
		}
		before = tmp;
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:26:44 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/13 18:13:17 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strjoin(char *a, char *b)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	ret = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (*(a + i))
	{
		*(ret + i) = *(a + i);
		i++;
	}
	j = 0;
	while (*(b + j))
	{
		*(ret + i + j) = *(b + j);
		j++;
	}
	*(ret + i + j) = '\0';
	free(a);
	return (ret);
}

int	buf_init(char **out, char **buf)
{
	*out = malloc(1);
	if (!*out)
		return (0);
	**out = '\0';
	*buf = malloc(BUF_SIZE + 1);
	if (!*buf)
	{
		free(*out);
		return (0);
	}
	return (1);
}

char	*read_file(int fd)
{
	char	*out;
	char	*buf;
	int		len;

	if (fd < 0)
		return (0);
	buf_init(&out, &buf);
	while (1)
	{
		len = read(fd, buf, BUF_SIZE);
		if (len <= 0)
			break ;
		buf[len] = '\0';
		out = ft_strjoin(out, buf);
		if (!out)
		{
			free(buf);
			return (0);
		}
	}
	free(buf);
	return (out);
}

int	get_x(char *file)
{
	int	x;
	int	is_sp;

	x = 0;
	is_sp = 1;
	while (*file)
	{
		if (is_sp && !((*file == ' ') || (*file == '\n')))
			x++;
		is_sp = ((*file == ' ') || (*file == '\n'));
		if (*file == '\n')
		{
			file++;
			break ;
		}
		file++;
	}
	return (x);
}

int	get_xy(char	*file, t_input *info)
{
	int	is_sp;
	int	row_x;
	int	total_count;

	info->x = get_x(file);
	row_x = 0;
	is_sp = 1;
	total_count = info->x;
	while (*file)
	{
		if (is_sp && !((*file == ' ') || (*file == '\n')))
			row_x++;
		if (*file == '\n')
		{
			total_count += row_x;
			if (row_x != info->x)
				return (INPUT_ERR);
			row_x = 0;
		}
		is_sp = ((*file == ' ') || (*file == '\n'));
		file++;
	}
	info->y = total_count / info->x + 1;
	return (RET_SUC);
}

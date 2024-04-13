/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:26:44 by seojepar          #+#    #+#             */
/*   Updated: 2024/04/13 15:08:44 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	get_x(char *file, t_dots *info)
{
	int	is_sp;
	int	exist_flag;
	int	cnt;

	is_sp = 1;
	exist_flag = 0;
	cnt = 0;
	while (*file)
	{
		if (is_sp && !is_blank(*file))
			cnt++;
		if (exist_flag && *file == '\n')
		{
			info->x = cnt;
			return (cnt);
		}
		if (!exist_flag && !is_blank(*file))
			exist_flag = 1;
		is_sp = is_blank(*file);
		file++;
	}
	info->x = cnt;
	return (cnt);
}

int	get_xy(char	*file, t_dots *info)
{
	int	is_sp;
	int	row_x;
	int	total_count;

	if (!get_x(file, info))
		return (RET_ERR);
	row_x = 0;
	is_sp = 1;
	total_count = 0;
	while (*file)
	{
		row_x += (is_sp && !((*file == ' ') || (*file == '\n')));
		if (*file == '\n')
		{
			total_count += row_x;
			if (row_x != 0 && row_x != info->x)
				return (INPUT_ERR);
			row_x = 0;
		}
		is_sp = ((*file == ' ') || (*file == '\n'));
		file++;
	}
	info->y = total_count / info->x;
	return (RET_SUC);
}

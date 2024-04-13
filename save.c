/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:00 by seojepar          #+#    #+#             */
/*   Updated: 2024/04/13 14:47:16 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	init_info(t_dots *info)
{
	int	x;
	int	y;
	int	i;

	x = info->x;
	y = info->y;
	info->dot = (t_coord **)malloc(sizeof(t_coord *) * x);
	if (!info->dot)
		return (RET_ERR);
	i = 0;
	while (i < x)
	{
		info->dot[i] = (t_coord *)malloc(sizeof(t_coord) * y);
		if (!info->dot[i])
		{
			while (i >= 0)
				free(info->dot[i--]);
			free(info->dot);
			free(info);
			return (RET_ERR);
		}
		i++;
	}
	return (RET_SUC);
}

void	save_dots(char *buf, t_dots *info)
{
	int	x;
	int	y;
	int	sp;

	x = 0;
	y = 0;
	sp = 1;
	while (*buf)
	{
		if (sp && *buf != ' ' && *buf != '\n')
		{
			info->dot[x][y].z = ft_atoi(&buf);
			info->dot[x][y].color = ft_0xatoi(buf);
			if (!*buf)
				break ;
			x++;
		}
		sp = (*buf == ' ' || *buf == '\n');
		if (*buf == '\n')
		{
			x = 0;
			y++;
		}
		buf++;
	}
}

t_dots	*store(int fd)
{
	char	*buf;
	t_dots	*info;

	buf = read_file(fd);
	if (!buf)
		return (RET_ERR);
	info = malloc(sizeof(t_dots));
	if (!info || !get_xy(buf, info) || !init_info(info))
	{
		free(buf);
		return (RET_ERR);
	}
	save_dots(buf, info);
	free(buf);
	return (info);
}

void	gen_dot(t_ptr *ptr, int x, int y)
{
	t_coord	**dots;
	float	z;
	double	d[2];
	double	i[2];

	dots = ptr->dots->dot;
	i[0] = (double)x;
	i[1] = (double)y;
	if (ptr->view.mk.mouseon == ON)
		rotate(x, y, i, ptr);
	z = dots[x][y].z * ptr->view.height;
	d[0] = i[0] - ptr->dots->x / 2;
	d[1] = i[1] - ptr->dots->y / 2;
	dots[x][y].cx = sqrt(3) * (d[0] - d[1]) / 2 * ptr->view.scale;
	dots[x][y].cx += ptr->view.x;
	dots[x][y].cy = ((d[0] + d[1]) / 2 - z) * ptr->view.scale;
	dots[x][y].cy += ptr->view.y;
}

void	make_img(t_ptr *ptr)
{
	int		i;
	int		j;
	t_coord	**dots;

	dots = ptr->dots->dot;
	i = 0;
	while (i < ptr->dots->x)
	{
		j = 0;
		while (j < ptr->dots->y)
		{
			gen_dot(ptr, i, j);
			if (i > 0)
				plot_line(dots[i - 1][j], dots[i][j], *ptr);
			if (j > 0)
				plot_line(dots[i][j - 1], dots[i][j], *ptr);
			j++;
		}
		i++;
	}
}

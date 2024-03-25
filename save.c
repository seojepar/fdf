/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:00 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/25 21:33:55 by seojeongpar      ###   ########.fr       */
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
		return (0);
	i = 0;
	while (i < x)
	{
		info->dot[i] = (t_coord *)malloc(sizeof(t_coord) * y);
		if (!info->dot[i])
			return (0);
		i++;
	}
	return (1);
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
		return (0);
	info = malloc(sizeof(t_dots));
	if (!info)
		return (0);
	if (!get_xy(buf, info))
		return (0);
	if (!init_info(info))
		return (0);
	save_dots(buf, info);
	return (info);
}

void	gen_dot(t_ptr *ptr, int x, int y)
{
	t_coord	**dots;
	float	z;
	float	di;
	float	dj;
	double	i;
	double	j;

	dots = ptr->dots->dot;
	i = (double)x;
	j = (double)y;
	if (ptr->view.mk.mouseon == ON)
		rotate(x,y,&i,&j,ptr);
	z = dots[x][y].z * ptr->view.height;
	di = i - ptr->dots->x / 2;
	dj = j - ptr->dots->y / 2;
	dots[x][y].cx = sqrt(3) * (di - dj) / 2 * ptr->view.scale;
	dots[x][y].cx += ptr->view.x;
	dots[x][y].cy = ((di + dj) / 2 - z) * ptr->view.scale;
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

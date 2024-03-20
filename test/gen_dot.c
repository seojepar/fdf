/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:00 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/20 10:56:20 by seojepar         ###   ########.fr       */
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

t_dots	*get_dots(int fd)
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

void	gen_dot(t_ptr *ptr, int i, int j)
{
	t_coord	**dots;
	float	z;
	float	di;
	float	dj;

	dots = ptr->dots->dot;
	z = dots[i][j].z * ptr->view.height;
	di = i - ptr->dots->x / 2;
	dj = j - ptr->dots->y / 2;
	dots[i][j].cx = sqrt(3) * (di - dj) / 2 * ptr->view.scale;
	dots[i][j].cx += ptr->view.x;
	dots[i][j].cy = ((di + dj) / 2 - z) * ptr->view.scale;
	dots[i][j].cy += ptr->view.y;
}

void	gen_dots(t_ptr *ptr)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:00 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/14 12:13:52 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	init_info(t_input *info)
{
	int	x;
	int	y;
	int	i;

	x = info->x;
	y = info->y;
	info->dot = (t_dot **)malloc(sizeof(t_dot *) * x);
	if (!info->dot)
		return (0);
	i = 0;
	while (i < x)
	{
		info->dot[i] = (t_dot *)malloc(sizeof(t_dot) * y);
		if (!info->dot[i])
			return (0);
		i++;
	}
	return (1);
}

void	save_dots(char *buf, t_input *info)
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

t_input	*get_input(int fd)
{
	char	*buf;
	t_input	*info;

	buf = read_file(fd);
	if (!buf)
		return (0);
	info = malloc(sizeof(t_input));
	if (!info)
		return (0);
	if (!get_xy(buf, info))
		return (0);
	if (!init_info(info))
		return (0);
	save_dots(buf, info);
	return (info);
}

void	dots_to_img(t_ptr *ptr)
{
	int		i;
	int		j;
	t_dot	**dots;

	i = -1;
	j = 0;
	dots = ptr->in->dot;
	while (++i < ptr->in->x)
	{
		j = 0;
		while (j < ptr->in->y)
		{
			dots[i][j].cx = (sqrt(3) * (i - j) / 2) * ptr->view.scale;
			dots[i][j].cx += WIN_X / 2 + ptr->view.x;
			dots[i][j].cy = (i + j) * ptr->view.scale / 2 + WIN_Y / 4;
			dots[i][j].cy += ptr->view.y - dots[i][j].z * ptr->view.height;
			if (dots[i][j].color < 0)
				dots[i][j].color = 0xFFFFFF;
			if (i > 0)
				plot_line(dots[i - 1][j], dots[i][j], *ptr);
			if (j > 0)
				plot_line(dots[i][j - 1], dots[i][j], *ptr);
			j++;
		}
	}
}

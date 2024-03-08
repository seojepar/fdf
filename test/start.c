/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:48:00 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/08 16:11:43 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	init_info(t_input *info)
{
	int	x;
	int	y;
	int i;

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
	int	x = 0;
	int	y = 0;
	int	sp = 1;
	while (*buf)
	{
		if (sp && *buf != ' ' && *buf != '\n')
		{
			info->dot[x][y].z = ft_atoi(&buf);
			info->dot[x][y].color = ft_0xatoi(buf);
			if (!*buf)
				break;
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
	char	*buf = read_file(fd);
	t_input	*info = malloc(sizeof(t_input));
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
	t_view	info = ptr->view;
	int		i = 0;
	int 	j = 0;
	t_input	*input = ptr->in;
	t_dot	**dots = input->dot;

	while (i < input->x)
	{
		j = 0;
		while (j < input->y)
		{
			dots[i][j].cx = (sqrt(3) * (i - j) / 2) * info.scale + 500;
			dots[i][j].cy = (i + j) * info.scale / 2 + 300 - dots[i][j].z * info.height;
			if (dots[i][j].color < 0)
				dots[i][j].color = 0xFFFFFF;
			if (i > 0)
				plot_line(dots[i - 1][j], dots[i][j], *ptr);
			if (j > 0)
				plot_line(dots[i][j - 1], dots[i][j], *ptr);
			j++;
		}
		i++;
	}
}
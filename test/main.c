/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/06 18:45:26 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"

void	img_pixel_put(t_ptr ptr, int x, int y, int color)
{
	char	*buffer;
	int		pixel;

	buffer = ptr.buf;
	pixel = y * ptr.line + x * 4;
	if (ptr.end == 1) // A first
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (ptr.end == 0) // B first
	{
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
}

int	key_handler(int key, void *arg)
{
	t_ptr	*tmp;

	tmp = ((t_ptr *)arg);
	if (key == ESC)
	{
		mlx_destroy_window(tmp->mlx, tmp->win);
		exit(1);
	}
	if (key == LEFT)
	{
		mlx_clear_window(tmp->mlx, tmp->win);
		tmp->x--;
		mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, tmp->x, tmp->y);
		printf("{%d %d}\n", tmp->x, tmp->y);
	}
	printf("%d key was pressed\n", key);
	return (1);
}

int	ft_get_xy(char *file, int *x, int *y)
{
	int	is_sp = 1;
	int	first_row_count = 0;
	int	other_row_count = 0;
	int	total_count;

	while (*file)
	{
		if (is_sp && !((*file == ' ') || (*file == '\n')))
			first_row_count++;
		is_sp = ((*file == ' ') || (*file == '\n'));
		if (*file == '\n')
		{
			file++;
			break;
		}
		file++;
	}
	total_count = first_row_count;
	while (*file)
	{
		if (is_sp && !((*file == ' ') || (*file == '\n')))
		{
			other_row_count++;
			total_count++;
		}
		if (*file == '\n')
		{
			if (other_row_count != first_row_count)
				return (INPUT_ERR);
			other_row_count = 0;
		}
		is_sp = ((*file == ' ') || (*file == '\n'));
		file++;
	}
	*x = first_row_count;
	*y = total_count / first_row_count;
	return (RET_SUC);
}

int	main(int argc, char *argv[])
{
	// 버퍼에 한번에 불러온다.
	char	*buf;
	buf = ft_read(open(argv[1], O_RDONLY));

	// x와 y 가져오기 + 파일 적합성 확인
	int	x;
	int	y;
	if (!ft_get_xy(buf, &x, &y))
		return (RET_ERR);

	// 점이라는 구조체의 배열을 동적배열로 선언해서 담자. 왜 굳이 동적배열?
	t_dot	**dots = (t_dot **)malloc(sizeof(t_dot *) * x);
	int	cx = 0;
	int	cy = 0;
	while (cy < x)
		dots[cy++] = (t_dot *)malloc(sizeof(t_dot) * y);
	int	sp = 1;
	cy = 0;
	while (*buf)
	{
		if (sp && *buf != ' ' && *buf != '\n')
		{
			dots[cx][cy].z = ft_atoi(&buf);
			dots[cx][cy].color = ft_0xatoi(buf);
			if (!*buf)
				break;
			cx++;
		}
		sp = (*buf == ' ' || *buf == '\n');
		if (*buf == '\n')
		{
			cx = 0;
			cy++;
		}
		buf++;
	}

	t_ptr	ptr;
	draw_dot(ptr, dots, x, y);
}

void	draw_dot(t_ptr ptr, t_dot **dots, int x, int y)
{
	int		scale = 40;
	int		mx = 0;
	int 	my = 0;
	int		i = 0;
	int 	j = 0;

	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, 1200, 1200, "Power Code");
	ptr.img = mlx_new_image(ptr.mlx, 1200, 1200);
	ptr.buf = mlx_get_data_addr(ptr.img, &ptr.pix, &ptr.line, &ptr.end);
	ptr.x = 0;
	ptr.y = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			dots[i][j].cx = (sqrt(3) * (i - j) / 2) * scale + 500;
			dots[i][j].cy = (i + j) * scale / 2 + 300 - dots[i][j].z * 3.5;
			if (dots[i][j].color < 0)
				dots[i][j].color = 0xFFFFFF;
			if (i > 0)
				plot_line(dots[i - 1][j], dots[i][j], ptr);
			if (j > 0)
				plot_line(dots[i][j - 1], dots[i][j], ptr);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, ptr.x, ptr.y);
	mlx_key_hook(ptr.win, key_handler, &ptr);
	mlx_loop(ptr.mlx);
}
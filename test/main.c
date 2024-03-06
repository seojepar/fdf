/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/06 09:02:24 by seojepar         ###   ########.fr       */
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
	t_ptr	tmp;

	tmp = *((t_ptr *)arg);
	if (key == ESC)
	{
		mlx_destroy_window(tmp.mlx, tmp.win);
		exit(1);
	}
	printf("%d key was pressed\n", key);
	return (1);
}
void	ft_get_xy(char *file, int *x, int *y)
{
	int	sp;

	*x = 0;
	*y = 0;
	sp = 1;

	while (*file)
	{
		if (!sp && (*file == ' ' || *file == '\n'))
			(*x)++;
		if (*file == '\n')
			(*y)++;
		sp = (*file == ' ');
		file++;
	}
	if ((*y) != 0)
		(*x) /= (*y);
}

int	main(int argc, char *argv[])
{
	// 버퍼에 한번에 불러온다.
	char	*buf;
	buf = ft_read(open(argv[1], O_RDONLY));

	// x와 y 가져오기
	int	x;
	int	y;
	ft_get_xy(buf, &x, &y);

	// 점이라는 구조체의 배열을 동적배열로 선언해서 담자. 왜 굳이 동적배열?
	t_dot	**dots = (t_dot **)malloc(sizeof(t_dot *) * x);
	int	i = 0;
	int	j = 0;
	while (j < x)
		dots[j++] = (t_dot *)malloc(sizeof(t_dot) * y);
	int	sp = 1;
	while (*buf)
	{
		if (sp && *buf != ' ' && *buf != '\n')
		{
			dots[i][j].z = ft_atoi(&buf);
			dots[i][j].color = ft_0xatoi(buf);
			printf("i: %d, j: %d, z: %d, color:%d\n", i, j, dots[i][j].z, dots[i][j].color);
			i++; 
		}
		if (*buf == '\n')
		{
			i = 0;
			j++;
		}
		sp = (*buf == ' ' || *buf == '\n');
		buf++;
	}

	// // 점을 찍고 이웃한 점을 연결하자.
	// t_ptr	ptr;
	// draw_dot(ptr, dots, x, y);
}

void	draw_dot(t_ptr ptr, t_dot **dots, int x, int y)
{
	int		scale = 40;
	int		mx = 0;
	int 	my = 0;
	int		i = 0;
	int 	j = 0;

	// 점을 그릴 기본창을 선언한다.
	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, 1200, 1200, "Power Code");
	ptr.img = mlx_new_image(ptr.mlx, 1200, 1200);
	ptr.buf = mlx_get_data_addr(ptr.img, &ptr.pix, &ptr.line, &ptr.end);
	// buffer: single array of width * height * 4 bytes. For a 500x500 image, we would need 1’000’000 bytes or about 0.953 MB.
	// edit buffer: set each pixel's color value by bit calculation.
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
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 0, 0);
	mlx_key_hook(ptr.win, key_handler, &ptr);
	mlx_loop(ptr.mlx);
}
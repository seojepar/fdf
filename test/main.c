/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/21 15:07:40 by seojeongpar      ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int		fd = open(argv[1], O_RDONLY);
	int		nbyte = 1000;
	char	*buf = malloc(nbyte + 1);
	char	*tmp;
	int		x;
	int		y;
	int		sp;
	t_ptr	ptr;

	read(fd, buf, nbyte);
	tmp = buf;
	x = 0;
	y = 0;
	sp = 1;
	while (*buf)
	{
		if (!sp && *buf == ' ' || *buf == '\n')
			x++;
		if (*buf == '\n')
			y++;
		sp = (*buf == ' ');
		buf++;
	}
	if (y != 0)
		x /= y;
	// x and y is done while this
	t_dot	**dots = (t_dot **)malloc(sizeof(t_dot *) * x);
	int	i = 0;
	int	j = 0;
	while (j < x)
		dots[j++] = (t_dot *)malloc(sizeof(t_dot) * y);
	i = 0;
	j = 0;
	sp = 1;
	while (*tmp)
	{
		if (sp && *tmp != ' ' && *tmp != '\n')
		{
			dots[i][j].z = ft_atoi(&tmp);
			dots[i][j].color = ft_0xatoi(tmp);
			i++;
		}
		if (*tmp == '\n')
		{
			i = 0;
			j++;
		}
		sp = (*tmp == ' ' || *tmp == '\n');
		tmp++;
	}
	draw_dot(ptr, dots, x, y);
}

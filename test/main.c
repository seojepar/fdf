/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/18 19:17:10 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"

char	*ft_substr(char *start, char *end)
{
	char	*out;
	int		i;

	out = (char *)malloc(end - start + 2);
	if (!out)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		*(out + i) = *(start + i);
		i++;
	}
	*(out + i) = '\0';
	return (out);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*out;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = malloc(len1 + len2 + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		out[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		out[len1 + i] = s2[i];
		i++;
	}
	free(s1);
	free(s2);
	return (out);
}

int	ft_0xatoi(char *str)
{
	int	num;

	if (*str != ',')
		return (-1);
	str++;
	num = 0;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 16 + *str - '0';
		else if ('A' <= *str && *str <= 'F')
			num = num * 16 + *str - 'A' + 10;
		else
			break ;
		str++;
	}
	return (num);
}

int	ft_atoi(char **str)
{
	int	flag;
	int	num;

	flag = 1;
	if (**str == '+')
		(*str)++;
	if (**str == '-')
	{
		flag = -1;
		(*str)++;
	}
	num = 0;
	while ('0' <= **str && **str <= '9')
	{
		num = num * 10 + **str - '0';
		(*str)++;
	}
	return (num * flag);
}

int	key_handler(int key, void *arg)
{
	t_ptr	tmp;

	tmp = *((t_ptr *)arg);
	if (key == 53)
	{
		mlx_destroy_window(tmp.mlx, tmp.win);
		exit(1);
	}
	printf("%d key was pressed\n", key);
	return (1);
}

void	draw_dot(t_dot **dots, int x, int y)
{
	t_ptr	ptr;
	void	*win_ptr;
	int	scale = 40;
	int	mx = 0;
	int my = 0;
	int	i = 0;
	int j = 0;

	ptr.mlx = mlx_init ();
	ptr.img = mlx_new_image(ptr.mlx, 1200, 1200);
	int	bpp, size_line, endian;
	char	*rely_on_me = mlx_get_data_addr(ptr.img, &bpp, &size_line, &endian);
	printf("%s", rely_on_me);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 500, 500);
	// printf("bits per pixel: %d\n size of line: %d\n endian: %d", bpp, size_line, endian);
	/*
	returns information about the created image, allowing a user to modify it later.
	bits_per_pixel will be filled with the number of bits needed to represent a pixel color (also called the depth of the image).
	size_line is the number of bytes used to store one line of the image in memory.  This information is needed to move from one line to another in the image. 
	endian tells you wether the pixel color in the image needs to be stored in little endian ( endian == 0), or big endian ( endian == 1).
	*/
	ptr.win = mlx_new_window(ptr.mlx, 1200, 1200, "Power Code");
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
	mlx_key_hook (ptr.win, key_handler, &ptr);
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
	draw_dot(dots, x, y);
}

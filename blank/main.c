/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/09 22:43:21 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "fdf.h"

typedef struct s_dot{
	int	cx; // current x
	int	cy;
	int	z;
	int	color;
}	t_dot;

void	draw_dot(t_dot **dots, int x, int y);

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
	printf("%d %d", x, y);
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
	printf("%d %d", x, y);
	draw_dot(dots, x, y);
}

void	draw_dot(t_dot **dots, int x, int y)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int	scale = 100;
	int	i = 0;
	int j = 0;


	mlx_ptr = mlx_init ();
	win_ptr = mlx_new_window(mlx_ptr, 1600, 1600, "Power Code");
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			dots[i][j].cx = (sqrt(3) * (i - j) / 2) * scale + 700;
			dots[i][j].cy = ((i + j) / 2 - dots[i][j].z) * scale + 500;
			if (dots[i][j].color < 0)
				dots[i][j].color = 0xFFFFFF;
			// printf("%d %d\n", dx, dy);
			mlx_pixel_put(mlx_ptr, win_ptr, dx, dy, dots[i][j].color);
			draw_line()
			j++;
		}
		i++;
	}
	mlx_loop(mlx_ptr);
}
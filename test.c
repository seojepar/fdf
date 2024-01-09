/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:42:15 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/09 13:32:11 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_x(char **my)
{
	int	x;

	x = 0;
	while (*(my + x))
		x++;
	return (x);
}

void	get_x_y(int fd, int *x, int *y)
{
	char	**tmp;
	char	*line;
	int		*point;

	*x = 0;
	*y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_split(line, ' ');
		free(line);
		*x = get_x(tmp);
		free(tmp);
		(*y)++;
	}
}

int	**set_point(int x_max, int y_max, int fd)
{
	int		**point;
	char	**tmp;
	char	*line;
	int		x;
	int		y;

	point = (int **)malloc(sizeof(int) * x_max * y_max);
	y = 0;
	while (y < y_max)
	{
		line = get_next_line(fd);
		tmp = ft_split(line, ' ');
		free(line);
		x = 0;
		while (x < x_max)
		{
			point[y][x] = ft_atoi(*tmp);
			x++;
			tmp++;
		}
		free(tmp);
		y++;
	}
	return (point);
}

int	main(int argc, char *argv[])
{
	int		fd;
	int		x_max;
	int		y_max;
	char	**tmp;
	int		**points;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	get_x_y(fd, &x_max, &y_max);
	printf("x_max is :%d, y_max is :%d", x_max, y_max);
	// close(fd);
	// fd = open(argv[1], O_RDONLY);
	// points = set_point(x_max, y_max, fd);
	// close(fd);
	
}

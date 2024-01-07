/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:42:15 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/07 19:34:47 by seojeongpar      ###   ########.fr       */
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

void	set_point(int *point, int x_max, int y_max, int fd);
{
	char	**tmp;
	char	*line;
	int		points;
	int		x;
	int 	y;

	x = 0;
	y = 0;
	point = &points;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_split(line, ' ');
		free(line);
		x = 0;
		while (*tmp)
		{
			points[x][y] = ft_atoi(*tmp);
			y++;
			tmp++;
		}
		free(tmp);
		x++;
	}
}

int	main(int argc, char *argv[])
{
	int			fd;
	int			x_max;
	int			y_max;
	char		**tmp;
	const char	*filename;
	int			*point;

	if (argc != 2)
		return (0);
	filename = (const char *)argv[1];
	fd = open(filename, O_RDONLY);
	get_x_y(fd, &x_max, &y_max);
	close(fd);
	point = (int *)malloc(sizeof(int) * x_max * y_max);
	
	// 저번에도 그랬지만 이 파싱하는게 생각보다 까다롭다. 스트레스 받고.
	// 중복해서 같은 작업을 두번 처리한다는 것도 뭔가 마음에 안든다.
}

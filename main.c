/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:38:03 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/04 15:53:59 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_row_num(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\n')
			i++;
		str++;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	int		i;
	int		x;
	int		y;
	int		**map;
	char	*text;
	char	*total;
	void	*mlx_ptr;
	void	*win_ptr;
	char	buf[BUFFER_SIZE + 1];

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window (mlx_ptr, 1000, 1000, "seojepar");
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (i <= BUFFER_SIZE)
		buf[i++] = '\0';
	read(fd, buf, BUFFER_SIZE);
	row = get_row_num(buf);
	map = (int **)malloc(sizeof(int *) * row);
	y = 0;
	
	// 문제: x가 얼마인지 알 수가 없다. 받아와야 함. 
	while (y < row)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x])
			px = sqrt(3) * (x - y) / 2;
			py = (x + y) / 2 - z;
			mlx_pixel_put (mlx_ptr, win_ptr, px, py, 0xFFFFFF);
			x++;
		}
		y++;
	}
	i = 0;
	while (i < row)
	{
		
		map[i] = ft_split(get_next_line(fd), ' ');
		i++;
	}
	// map[x][y] = z 다 라고 설정이 되어있을거다. 그럼 이거를 px, py 값으로 변환해서 좌표를 찍어준다.
	
	// https://wonit.tistory.com/527 : 2차원 배열은 사실 1차원으로 저장된다.
	// 줄이 몇줄인지 알아낼 수 있는 방법은 없을까?
}

1. parse map: int[x][y] = z save
2. x, y, z into 2D coordinates
3. 
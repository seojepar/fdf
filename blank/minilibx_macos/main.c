/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:12:03 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/09 21:16:04 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

int	fp(void	*par)
{
	par++;
	return (1);
}

// int main()
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init ();
// 	win_ptr = mlx_new_window(mlx_ptr, 1000, 2000, "Title");
// 	mlx_pixel_put(mlx_ptr, win_ptr, 500, 500, 0xFFFFFF);
// 	mlx_string_put(mlx_ptr, win_ptr, 500, 700, 0xFFFFFF, "Hi I am");
// 	mlx_loop(mlx_ptr);
// 	mlx_key_hook(win_ptr, fp, "P");
// 	return (1);
// }

void	ft_switch(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// bresenham
void	draw_line(int x0, int y0, int x1, int y1)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		dx;
	int		dy;
	int		D;
	int		tmp;
	int		yi;

	mlx_ptr = mlx_init ();
	win_ptr = mlx_new_window(mlx_ptr, 200, 200, "Title");
	mlx_pixel_put(mlx_ptr, win_ptr, 100, 100, 0xFFFFFF);
	//	cmd 찍고 들어가보면 색깔이 int 임을 알 수 있어요.
	if (x0 > x1)
	{
		ft_switch(&x0, &x1);
		ft_switch(&y0, &y1);
	}

	dx = x1 - x0;
	dy = y1 - y0;
	D = 2 * dy - dx;
	yi = 0;
	if (y1 < y0)
		yi = -1;

	while (x0 != x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0 + yi * (D > 0), 0xFFFFFF);
		x0++;
		if (D > 0)
		{
			y0 += 1 + yi;
			D += dy - dx;
		}
		else
			y0 += yi;
			D += dy;
	}
	mlx_loop(mlx_ptr);
}

int main()
{
	draw_line(10, 100, 70, 0);
	// draw_line(80, 20, 20, 100);
}
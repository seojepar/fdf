/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:12:03 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/02 17:36:20 by seojeongpar      ###   ########.fr       */
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

// bresenham
void	draw_line(int x0, int y0, int x1, int y1)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		dx;
	int		dy;
	int		D;

	mlx_ptr = mlx_init ();
	win_ptr = mlx_new_window(mlx_ptr, 200, 200, "Title");
	mlx_pixel_put(mlx_ptr, win_ptr, 100, 100, 0xFFFFFF);
	dx = x1 - x0;
	dy = y1 - y0;
	D = 2 * dy - dx;

	while (x0 != x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0 + (D > 0), 0xFFFFFF);
		x0++;
		if (D > 0)
		{
			y0++;
			D += dy - dx;
		}
		else
			D += dy;
	}
	mlx_loop(mlx_ptr);
}

int main()
{
	draw_line(10, 20, 70, 100);
}
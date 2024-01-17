/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:50:42 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/17 20:50:31 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>

void	plot_dot(t_dot d, void *mlx_ptr, void *win_ptr)
{
	mlx_pixel_put(mlx_ptr, win_ptr, d.cx, d.cy, d.color);
}

void	plot_line_high(t_dot d1, t_dot d2, void *mlx_ptr, void *win_ptr)
{
	int	dx;
	int	dy;
	int	xi;
	int	dis;

	dx = d2.cx - d1.cx;
	dy = d2.cy - d1.cy;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	dis = 2 * dx - dy;
	while (d1.cy <= d2.cy)
	{
		plot_dot(d1, mlx_ptr, win_ptr);
		d1.cy++;
		if (dis > 0)
		{
			d1.cx = d1.cx + xi;
			dis = dis + 2 * (dx - dy);
		}
		else
			dis = dis + 2 * dx;
	}
}

void	plot_line_low(t_dot d1, t_dot d2, void *mlx_ptr, void *win_ptr)
{
	int	dx;
	int	dy;
	int	yi;
	int	dis;

	dx = d2.cx - d1.cx;
	dy = d2.cy - d1.cy;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	dis = 2 * dy - dx;
	while (d1.cx <= d2.cx)
	{
		plot_dot(d1, mlx_ptr, win_ptr);
		d1.cx++;
		if (dis > 0)
		{
			d1.cy = d1.cy + yi;
			dis = dis + 2 * (dy - dx);
		}
		else
			dis = dis + 2 * dy;
	}
}

void	plot_line(t_dot d1, t_dot d2, void *mlx_ptr, void *win_ptr)
{
	if (abs(d1.cx - d2.cx) < abs(d1.cy - d2.cy))
	{
		if (d1.cy > d2.cy)
			plot_line_high(d2, d1, mlx_ptr, win_ptr);
		else
			plot_line_high(d1, d2, mlx_ptr, win_ptr);
	}
	else
	{
		if (d1.cx > d2.cx)
			plot_line_low(d2, d1, mlx_ptr, win_ptr);
		else
			plot_line_low(d1, d2, mlx_ptr, win_ptr);
	}
}

int	fp(int button, int x, int y, void *param)
{
	printf("button:%d, x:%d, y:%d\n", button, x, y);
	return (1);
}

int main()
{
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Title");
	t_dot	dotdot1;
	t_dot	dotdot2;

	dotdot1.cx = 1;
	dotdot1.cy = 800;
	dotdot2.cx = 500;
	dotdot2.cy = 200;
	plot_line(dotdot1, dotdot2, mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
	mlx_mouse_hook(win_ptr, fp, (void *)0);
}

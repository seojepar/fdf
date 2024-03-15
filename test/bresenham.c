/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:50:42 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/14 12:24:32 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	plot_line(t_dot d1, t_dot d2, t_ptr ptr)
{
	if (out_of_win(d1, d2))
		return ;
	if (abs(d1.cx - d2.cx) < abs(d1.cy - d2.cy))
	{
		if (d1.cy > d2.cy)
			plot_line_high(d2, d1, ptr);
		else
			plot_line_high(d1, d2, ptr);
	}
	else
	{
		if (d1.cx > d2.cx)
			plot_line_low(d2, d1, ptr);
		else
			plot_line_low(d1, d2, ptr);
	}
}

void	plot_line_high(t_dot d1, t_dot d2, t_ptr ptr)
{
	t_dot	dc;
	int		dx;
	int		dy;
	int		xi;
	int		dis;

	dx = d2.cx - d1.cx;
	dy = d2.cy - d1.cy;
	xi = (dx >= 0) * 2 - 1;
	dx *= (dx >= 0) * 2 - 1;
	dc = d1;
	dis = 2 * dx - dy;
	while (dc.cy < d2.cy)
	{
		dc.color = gen_color(d1, d2, dc, 2);
		plot_dot(dc, ptr);
		dc.cy++;
		if (dis > 0)
		{
			dc.cx = dc.cx + xi;
			dis = dis + 2 * (dx - dy);
		}
		else
			dis = dis + 2 * dx;
	}
}

void	plot_line_low(t_dot d1, t_dot d2, t_ptr ptr)
{
	t_dot	dc;
	int		dx;
	int		dy;
	int		yi;
	int		dis;

	dx = d2.cx - d1.cx;
	dy = d2.cy - d1.cy;
	yi = (dy >= 0) * 2 - 1;
	dy *= (dy >= 0) * 2 - 1;
	dis = 2 * dy - dx;
	dc = d1;
	while (dc.cx < d2.cx)
	{
		dc.color = gen_color(d1, d2, dc, 1);
		plot_dot(dc, ptr);
		dc.cx++;
		if (dis > 0)
		{
			dc.cy = dc.cy + yi;
			dis = dis + 2 * (dy - dx);
		}
		else
			dis = dis + 2 * dy;
	}
}

int	out_of_win(t_dot d1, t_dot d2)
{
	int	x;

	x = !(0 <= d1.cx && d1.cx <= WIN_X) && !(0 <= d2.cx && d2.cx <= WIN_X);
	x = x || (!(0 <= d1.cy && d1.cy <= WIN_Y) && !(0 <= d2.cy && d2.cy <= WIN_Y));
	return (x);
}

void	plot_dot(t_dot d, t_ptr ptr)
{
	if (0 <= d.cx && d.cx < WIN_X && 0 <= d.cy && d.cy < WIN_Y)
		img_pixel_put(ptr, d.cx, d.cy, d.color);
}
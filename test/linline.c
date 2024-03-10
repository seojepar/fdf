/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:50:42 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/10 17:00:22 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	plot_dot(t_dot d, t_ptr ptr)
{
	if (0 <= d.cx && d.cx < WIN_X && 0 <= d.cy && d.cy < WIN_Y)
		img_pixel_put(ptr, d.cx, d.cy, d.color);
}

int	int_div(int m, int n, int x, int y)
{
	x &= 255;
	y &= 255;
	return ((m * y + n * x) / (m + n));
}

int	gen_color(t_dot d1, t_dot d2, t_dot dc, int flag)
{
	int	ret;
	int	m;
	int	n;

	if (flag == 1)
	{
		m = dc.cx - d1.cx;
		n = d2.cx - dc.cx;
	}
	if (flag == 2)
	{
		m = dc.cy - d1.cy;
		n = d2.cy - dc.cy;
	}
	ret = int_div(m, n, d1.color, d2.color);
	ret = (ret << 8) + int_div(m, n, d1.color >> 8, d2.color >> 8);
	ret = (ret << 8) + int_div(m, n, d1.color >> 16, d2.color >> 16);
	return (ret);
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
	xi = 1;
	dc.cx = d1.cx;
	dc.cy = d1.cy;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
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
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	dis = 2 * dy - dx;
	dc.cx = d1.cx;
	dc.cy = d1.cy;
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

int	in_win(t_dot d1, t_dot d2)
{
	int	x;
	x = (0 <= d1.cx && d1.cx <= WIN_X) && (0 <= d2.cx && d2.cx <= WIN_X);
	x = x && (0 <= d1.cy && d1.cy <= WIN_Y) && (0 <= d2.cy && d2.cy <= WIN_Y);
	return (x);
}

void	plot_line(t_dot d1, t_dot d2, t_ptr ptr)
{
	if (!in_win(d1, d2))
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

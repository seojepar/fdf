/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:50:42 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/08 16:41:38 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	plot_dot(t_dot d, t_ptr ptr)
{
	// mlx_pixel_put(ptr.mlx, ptr.win, d.cx, d.cy, d.color);
	// printf("%d %d\n", d.cx, d.cy);
	// d.cx 나 d.cy 가 1200 '이상' 이 되기만 해도 버퍼 오버플로우가 발생했다.
	if (0 <= d.cx && d.cx < 1200 && 0 <= d.cy && d.cy < 1200)
		img_pixel_put(ptr, d.cx, d.cy, d.color);
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
		dc.color = ((d2.cy - dc.cy) * d1.color + (dc.cy - d1.cy) * d2.color) / (d2.cy - d1.cy);
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
		dc.color = ((d2.cx - dc.cx) * d1.color + (dc.cx - d1.cx) * d2.color) / (d2.cx - d1.cx);
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

void	plot_line(t_dot d1, t_dot d2, t_ptr ptr)
{
	if ((d1.cx < 0 && d2.cx <0) || (d1.cy < 0 && d2.cy < 0))
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

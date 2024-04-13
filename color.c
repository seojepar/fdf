/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:06:03 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/04/13 14:50:28 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	div_color(int m, int n, int c1, int c2)
{
	c1 &= 255;
	c2 &= 255;
	return ((m * c2 + n * c1) / (m + n));
}

int	gen_color(t_coord d1, t_coord d2, t_coord dc, int flag)
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
	ret = div_color(m, n, d1.color >> 16, d2.color >> 16);
	ret = (ret << 8) + div_color(m, n, d1.color >> 8, d2.color >> 8);
	ret = (ret << 8) + div_color(m, n, d1.color, d2.color);
	return (ret);
}

void	img_pixel_put(t_ptr ptr, int x, int y, int color)
{
	char	*buffer;
	int		pixel;

	buffer = ptr.buf;
	pixel = y * ptr.line + x * ptr.pix / 8;
	if (ptr.end == 1)
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (ptr.end == 0)
	{
		// 뒤에서부터 들어가게 됨. B G R A 이렇게..
		// *(unsigned int *)buffer = color & 0x00ffffff;
		// buffer[pixel + 0] = 0;
		// buffer[pixel + 1] = 0;
		// buffer[pixel + 2] = 0xFF;
		// buffer[pixel + 3] = 0;
		// 이렇게 하니 전체적으로 다 빨간색이 나옴을 알 수 있었다. 
		// 즉, 색깔 자체가 잘 못 들어가는게 거의 확실하다.
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
}

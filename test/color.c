/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:06:03 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/14 12:14:28 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	div_color(int m, int n, int c1, int c2)
{
	c1 &= 255;
	c2 &= 255;
	return ((m * c2 + n * c1) / (m + n));
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
	ret = div_color(m, n, d1.color, d2.color);
	ret = (ret << 8) + div_color(m, n, d1.color >> 8, d2.color >> 8);
	ret = (ret << 8) + div_color(m, n, d1.color >> 16, d2.color >> 16);
	return (ret);
}

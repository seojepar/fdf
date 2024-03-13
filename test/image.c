/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:49:34 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/13 18:13:58 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pixel_put(t_ptr ptr, int x, int y, int color)
{
	char	*buffer;
	int		pixel;

	buffer = ptr.buf;
	pixel = y * ptr.line + x * 4;
	if (ptr.end == 1)
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (ptr.end == 0)
	{
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
}

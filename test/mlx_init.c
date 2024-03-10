/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:07 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/10 17:03:02 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	hooks(t_ptr	ptr)
{
	mlx_key_hook(ptr.win, key_handler, &ptr);
	mlx_expose_hook(ptr.win, expose_handler, &ptr);
	mlx_hook(ptr.win, ON_DESTROY, 0, ft_close, &ptr);
	mlx_mouse_hook(ptr.win, mouse_on, &ptr);
	mlx_hook(ptr.win, ON_MOUSEUP, 0, mouse_off, &ptr);
	mlx_loop(ptr.mlx);
}

void	init_mlx(t_ptr *ptr)
{
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 1200, 1200, "Power Code");
	ptr->img = mlx_new_image(ptr->mlx, 1200, 1200);
	ptr->buf = mlx_get_data_addr(ptr->img, &ptr->pix, &ptr->line, &ptr->end);
	ptr->view.x = 0;
	ptr->view.y = 0;
	ptr->view.scale = 40;
	ptr->view.height = 3.5;
}

void	reset_buf(t_ptr ptr)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1200)
	{
		j = 0;
		while (j < 1200)
			img_pixel_put(ptr, i, j++, 0);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:07 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/15 14:13:45 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	hooks(t_ptr	ptr)
{
	mlx_key_hook(ptr.win, key_handler, &ptr);
	mlx_mouse_hook(ptr.win, mouse_on, &ptr);
	mlx_hook(ptr.win, ON_MOUSEUP, 0, mouse_off, &ptr);
	mlx_hook(ptr.win, ON_DESTROY, 0, ft_close, &ptr);
	mlx_loop(ptr.mlx);
}

void	init_mlx(t_ptr *ptr)
{
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 1200, 1200, "Power Code");
	ptr->img = mlx_new_image(ptr->mlx, 1200, 1200);
	ptr->buf = mlx_get_data_addr(ptr->img, &ptr->pix, &ptr->line, &ptr->end);
	ptr->view.x = WIN_X / 2;
	ptr->view.y = WIN_Y / 2;
	ptr->view.scale = 40;
	ptr->view.height = 0.12;
	ptr->view.mouse.mx = -1;
	ptr->view.mouse.mx = -1;
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

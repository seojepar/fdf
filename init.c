/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:07 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/25 21:12:52 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	events(t_ptr	ptr)
{
	mlx_hook(ptr.win, ON_KEYDOWN, 0, key_dn, &ptr);
	mlx_hook(ptr.win, ON_MOUSEDN, 0, mouse_on, &ptr);
	mlx_hook(ptr.win, ON_MOUSEUP, 0, mouse_off, &ptr);
	mlx_hook(ptr.win, ON_MOUSEMOVE, 0, mouse_move, &ptr);
	mlx_hook(ptr.win, ON_DESTROY, 0, ft_close, &ptr);
	mlx_loop_hook(ptr.mlx, main_loop, &ptr);
	mlx_loop(ptr.mlx);
}

void	init(t_ptr *ptr)
{
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 1200, 1200, "fdf");
	ptr->img = mlx_new_image(ptr->mlx, 1200, 1200);
	ptr->buf = mlx_get_data_addr(ptr->img, &ptr->pix, &ptr->line, &ptr->end);
	ptr->view.x = WIN_X / 2;
	ptr->view.y = WIN_Y / 2;
	ptr->view.scale = 40;
	ptr->view.height = 0.12;
	ptr->view.mk.mx = -1;
	ptr->view.mk.mx = -1;
	ptr->view.mk.mouseon = OFF;
	ptr->view.mk.keyon = OFF;
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

int	main_loop(t_ptr *ptr)
{
	reset_buf(*ptr);
	make_img(ptr);
	mlx_clear_window(ptr->mlx, ptr->win);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 0, 0);
	return (0);
}
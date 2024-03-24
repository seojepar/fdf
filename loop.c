/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/24 17:18:54 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	key_handler(int key, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	ptr->view.mk.keyon = 1;
	while(ptr->view.mk.keyon)
	{
		if (key == ESC)
			ft_close(ptr);
		ptr->view.x += (-1) * (key == LEFT) + (key == RIGHT);
		ptr->view.y += (-1) * (key == UP) + (key == DOWN);
		ptr->view.scale += (-1) * (key == MINUS) + 1 * (key == PLUS);
		ptr->view.height += (-0.02) * (key == PGDN) + 0.02 * (key == PGUP);
		reset_buf(*ptr);
		make_img(ptr);
		mlx_clear_window(ptr->mlx, ptr->win);
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 0, 0);
	}
	return (1);
}

int	mouse_on(int button, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (button != SCROLL_DN && button != SCROLL_UP)
	{
		ptr->view.mk.mouseon = 1;
		mlx_hook(ptr->win, ON_MOUSEMOVE, 0, mouse_move, param);
	}
	ptr->view.y += (-1) * (button == SCROLL_DN) + (button == SCROLL_UP);
	reset_buf(*ptr);
	make_img(ptr);
	mlx_clear_window(ptr->mlx, ptr->win);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 0, 0);
	return (1);
}

int	mouse_off(int button, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (button != 5 && button != 4)
	{
		ptr->view.mk.mouseon = 0;
		ptr->view.mk.mx = -1;
		ptr->view.mk.mx = -1;
	}
	return (RET_SUC);
}

int	mouse_move(int x, int y, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (ptr->view.mk.mouseon == 0)
		return (0);
	ptr->view.mk.mx = x;
	ptr->view.mk.mx = y;
	return (1);
}

int	ft_close(t_ptr *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	free(ptr->mlx);
	exit(1);
	return (0);
}

int key_up(void *param){
	t_ptr	*ptr;
	
	ptr = (t_ptr *)param;
	ptr->view.mk.keyon = 0;
	return (0);
}

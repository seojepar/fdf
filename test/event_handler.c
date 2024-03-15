/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/14 12:10:48 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	key_handler(int key, void *arg)
{
	t_ptr	*tmp;

	tmp = ((t_ptr *)arg);
	if (key == ESC)
		ft_close(tmp);
	tmp->view.x += (-1) * (key == LEFT) + (key == RIGHT);
	tmp->view.y += (-1) * (key == UP) + (key == DOWN);
	tmp->view.scale += (-5) * (key == MINUS) + 5 * (key == PLUS);
	tmp->view.height += (-0.2) * (key == PGDN) + 0.2 * (key == PGUP);
	reset_buf(*tmp);
	dots_to_img(tmp);
	mlx_clear_window(tmp->mlx, tmp->win);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
	return (1);
}

int	mouse_on(int button, int x, int y, void *param)
{
	t_ptr	*tmp;

	tmp = (t_ptr *)param;
	if (button != 5 && button != 4)
	{
		tmp->view.mouse = 1;
		mlx_hook(tmp->win, ON_MOUSEMOVE, 0, mouse_move, param);
	}
	tmp->view.y += (-1) * (button == 5) + (button == 4);
	reset_buf(*tmp);
	dots_to_img(tmp);
	mlx_clear_window(tmp->mlx, tmp->win);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
	return (1);
}

int	mouse_off(int button, int x, int y, void *param)
{
	if (button != 5 && button != 4)
		((t_ptr *)param)->view.mouse = 0;
	return (RET_SUC);
}

int	ft_close(t_ptr *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	free(ptr->mlx);
	exit(1);
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_ptr	*tmp;

	tmp = (t_ptr *)param;
	if (tmp->view.mouse == 0)
		return (0);
	return (1);
}

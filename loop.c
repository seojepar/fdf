/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/24 13:01:41 by seojepar         ###   ########.fr       */
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
	tmp->view.scale += (-1) * (key == MINUS) + 1 * (key == PLUS);
	tmp->view.height += (-0.02) * (key == PGDN) + 0.02 * (key == PGUP);
	reset_buf(*tmp);
	gen_dots(tmp);
	mlx_clear_window(tmp->mlx, tmp->win);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
	return (1);
}

int	mouse_on(int button, void *param)
{
	t_ptr	*tmp;

	tmp = (t_ptr *)param;
	if (button != SCROLL_DN && button != SCROLL_UP)
	{
		tmp->view.mouse.onoff = 1;
		mlx_hook(tmp->win, ON_MOUSEMOVE, 0, mouse_move, param);
	}
	tmp->view.y += (-1) * (button == SCROLL_DN) + (button == SCROLL_UP);
	reset_buf(*tmp);
	gen_dots(tmp);
	mlx_clear_window(tmp->mlx, tmp->win);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, 0, 0);
	
	return (1);
}

int	mouse_off(int button, void *param)
{
	t_ptr	*tmp;

	tmp = (t_ptr *)param;
	if (button != 5 && button != 4)
	{
		tmp->view.mouse.onoff = 0;
		tmp->view.mouse.mx = -1;
		tmp->view.mouse.mx = -1;
	}
	return (RET_SUC);
}

int	mouse_move(int x, int y, void *param)
{
	t_ptr	*tmp;

	tmp = (t_ptr *)param;
	if (tmp->view.mouse.onoff == 0)
		return (0);
	tmp->view.mouse.mx = x;
	tmp->view.mouse.mx = y;
	return (1);
}

int	ft_close(t_ptr *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	free(ptr->mlx);
	error("Window closed", 1);
	return (0);
}

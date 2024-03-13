/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/13 18:14:12 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	key_handler(int key, void *arg)
{
	t_ptr	*tmp;

	tmp = ((t_ptr *)arg);
	if (key == ESC)
	{
		mlx_destroy_window(tmp->mlx, tmp->win);
		exit(1);
	}
	if (key == LEFT)
		tmp->view.x--;
	if (key == RIGHT)
		tmp->view.x++;
	if (key == UP)
		tmp->view.y--;
	if (key == DOWN)
		tmp->view.y++;
	if (key == MINUS)
		tmp->view.scale -= 5;
	if (key == PLUS)
		tmp->view.scale += 5;
	if (key == PGDN)
		tmp->view.height -= 0.2;
	if (key == PGUP)
		tmp->view.height += 0.2;
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
	printf("button: %d, x: %d, y: %d\n", button, x, y);
	if (button == 5)
		tmp->view.y--;
	if (button == 4)
		tmp->view.y++;
	mlx_clear_window(tmp->mlx, tmp->win);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, tmp->view.x, tmp->view.y);
	return (1);
}

int	mouse_off(int button, int x, int y, void *param)
{
	if (button != 5 && button != 4)
		((t_ptr	*)param)->view.mouse = 0;
	return (RET_SUC);
}

int	expose_handler(void *param)
{
	printf("Expose handler was called");
	return (RET_SUC);
}

int	ft_close(t_ptr *ptr)
{
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
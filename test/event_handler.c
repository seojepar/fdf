/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/08 16:15:26 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	key_handler(int key, void *arg)
{
	t_ptr	*tmp;
	t_view	view;

	tmp = ((t_ptr *)arg);
	view = tmp->view;
	if (key == ESC)
	{
		mlx_destroy_window(tmp->mlx, tmp->win);
		exit(1);
	}
	if (key == LEFT)
		view.x--;
	if (key == RIGHT)
		view.x++;
	if (key == UP)
		view.y--;
	if (key == DOWN)
		view.y++;
	if (key == PGDN)
	mlx_clear_window(tmp->mlx, tmp->win);
	mlx_put_image_to_window(tmp->mlx, tmp->win, tmp->img, tmp->view.x, tmp->view.y);
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
	// called when 다른 창에 포커스가 집중되어있다가 바뀔 때
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
	printf("%d %d\n", x, y);
	return (1);
}
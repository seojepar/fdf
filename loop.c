/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/27 14:27:06 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int	key_dn(int key, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	ptr->view.mk.keyon = 1;
	if (key == ESC)
		ft_close(ptr);
	ptr->view.x += (-1) * (key == LEFT) + (key == RIGHT);
	ptr->view.y += (-1) * (key == UP) + (key == DOWN);
	ptr->view.scale += (-1) * (key == MINUS) + 1 * (key == PLUS);
	if (ptr->view.scale <= 0)
		ptr->view.scale = 0;
	ptr->view.height += (-0.02) * (key == PGDN) + 0.02 * (key == PGUP);
	return (RET_SUC);
}

int	mouse_on(int button, int x, int y, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (button != SCROLL_DN && button != SCROLL_UP)
	{
		ptr->view.mk.mouseon = ON;
		ptr->view.mk.ox = x;
		ptr->view.mk.oy = y;
		ptr->view.mk.mx = x;
		ptr->view.mk.my = y;
	}
	ptr->view.y += (-1) * (button == SCROLL_DN) + (button == SCROLL_UP);
	return (RET_SUC);
}

int	mouse_off(int button, int x, int y, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (button != SCROLL_DN && button != SCROLL_UP)
		ptr->view.mk.mouseon = OFF;
	ptr->view.mk.ox = -1;
	ptr->view.mk.oy = -1;
	ptr->view.mk.mx = x;
	ptr->view.mk.my = y;
	return (RET_SUC);
}

int	mouse_move(int x, int y, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (ptr->view.mk.mouseon == OFF)
		return (0);
	ptr->view.mk.mx = x;
	ptr->view.mk.my = y;
	return (RET_SUC);
}

int	ft_close(t_ptr *ptr)
{
	int		i;
	t_coord	**dot;

	dot = ptr->dots->dot;
	i = 0;
	while(i < ptr->dots->x)
	{
		free(dot[i]);
		i++;
	}
	free(dot);
	mlx_destroy_window(ptr->mlx, ptr->win);
	mlx_destroy_image(ptr->mlx, ptr->img);
	free(ptr->mlx);
	exit(1);
	return (RET_SUC);
}

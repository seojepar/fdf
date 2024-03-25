/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/25 21:37:32 by seojeongpar      ###   ########.fr       */
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
	if (button != SCROLL_DN && button != SCROLL_UP){
		ptr->view.mk.mouseon = ON;
		ptr->view.mk.ox = x;
		ptr->view.mk.oy = y;
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
	printf("mx: %d my: %d\n",x, y);
	ptr->view.mk.mx = x;
	ptr->view.mk.mx = y;
	return (RET_SUC);
}

int	ft_close(t_ptr *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	free(ptr->mlx);
	exit(1);
	return (RET_SUC);
}


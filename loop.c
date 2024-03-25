/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/25 20:48:09 by seojeongpar      ###   ########.fr       */
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
	return (1);
}


int	mouse_on(int button, int x, int y, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (button != SCROLL_DN && button != SCROLL_UP)
		ptr->view.mk.mouseon = 1;
	ptr->view.y += (-1) * (button == SCROLL_DN) + (button == SCROLL_UP);
	ptr->view.mk.mx = x;
	ptr->view.mk.my = y;
	return (1);
}

// int	mouse_off(int button, void *param)
// {
// 	t_ptr	*ptr;

// 	ptr = (t_ptr *)param;
// 	if (button != 5 && button != 4)
// 		ptr->view.mk.mouseon = 0;
// 	return (RET_SUC);
// }

// int	mouse_move(int x, int y, void *param)
// {
// 	t_ptr	*ptr;

// 	ptr = (t_ptr *)param;
// 	if (ptr->view.mk.mouseon == 0)
// 		return (0);
// 	ptr->view.mk.mx = x;
// 	ptr->view.mk.mx = y;
// 	printf("MOUSE MOVE, %d %d\n", x, y);
// 	return (1);
// }

int	ft_close(t_ptr *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	free(ptr->mlx);
	exit(1);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:19:28 by seojepar          #+#    #+#             */
/*   Updated: 2024/03/27 13:20:40 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	line_pos(t_vect A, t_vect B){
	if (A.x < 0){
		A.x = -A.x;
		A.y = -A.y;
	}
	if (A.y * (B.x - A.x) + A.x * (A.y - B.y) < 0)
		return (UP);
	else
		return (DOWN);
}

double	get_angle(t_vect A, t_vect B){
	int		pos;
	double	angle;

	angle = acos(vect_ip(A, B) / (vect_size(A) * vect_size(B)));
	pos = line_pos(A,B);
	if ((A.x < 0 && pos == UP) || (A.x > 0 && pos == DOWN))
		angle = 2 * M_PI - angle;
	return (angle);
}

void rotate(double x, double y, double *i, double *j,t_ptr *ptr){
	double angle;

	angle = ptr->view.mk.angle;
	x -= ptr->dots->x / 2;
	y -= ptr->dots->y / 2;
	*i = x * cos(angle) - y * sin(angle) + ptr->dots->x / 2;
	*j = x * sin(angle) + y * cos(angle) + ptr->dots->y / 2;;
}

void	update_angle(t_ptr *ptr){
	t_vect V1;
	t_vect V2;

	if (ptr->view.mk.ox < 0 || \
	(ptr->view.mk.ox == ptr->view.mk.mx\
	&& ptr->view.mk.oy == ptr->view.mk.my))
	{
		ptr->view.mk.angle = 0;
		return ;
	}
	V1 = make_vect(ptr->view.mk.ox, ptr->view.mk.oy, ptr);
	V2 = make_vect(ptr->view.mk.mx, ptr->view.mk.my, ptr);
	ptr->view.mk.angle = -get_angle(V1, V2);
}

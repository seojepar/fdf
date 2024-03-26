/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:15:25 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/26 15:01:49 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vect	make_vect(double cx, double cy, t_ptr *ptr){
	double	ox;
	double	oy;
	t_vect	ret;

	ox = ptr->view.x;
	oy = ptr->view.y;
	ret.x = +(cx - ox);
	ret.y = -(cy - oy);
	return (ret);
}

double	vect_size(t_vect A){
	return (sqrt(A.x * A.x + A.y * A.y));
}

int	vect_ip(t_vect A, t_vect B){
	return (A.x * B.x + A.y * B.y);
}

double	get_angle(t_vect A, t_vect B, t_view view){
	double	dx;
	double	dy;
	double	angle;

	angle = acos(vect_ip(A, B) / (vect_size(A) * vect_size(B)));
	dx = A.x - view.x;
	dy = A.y - view.y;
	if (dy == 0){
		if (B.y < A.y)
			angle = 2 * M_PI - angle;	
	}
	else if ((B.x - view.x) * dy / dx + view.y > B.y)
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
	ptr->view.mk.angle = get_angle(V1, V2, ptr->view);
	printf("THE FUCKING ANGLE IS %f\n", ptr->view.mk.angle * 180 / 3.1415);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:15:25 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/25 21:55:14 by seojeongpar      ###   ########.fr       */
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

double	get_angle(t_vect A, t_vect B){
	return (asin(vect_ip(A, B) / (vect_size(A) * vect_size(B))));
}

void rotate(int x, int y, double *i, double *j,t_ptr *ptr){
	double angle;
	t_vect V1;
	t_vect V2;
	// ox, oy 를 받아서 마이너스면 아무것도 안함.
	if (ptr->view.mk.ox < 0)
		return ;
	if (ptr->view.mk.ox == ptr->view.mk.mx\
	&& ptr->view.mk.oy == ptr->view.mk.my)
		return ;
	// ox, oy 에 비해서 mx, my가 몇도 회전 되었는지 계산한다.
	V1 = make_vect(ptr->view.mk.ox, ptr->view.mk.oy, ptr);
	V2 = make_vect(ptr->view.mk.mx, ptr->view.mk.my, ptr);
	angle = get_angle(V1, V2);
	printf("angle is %f\n", angle);
	// 그만큼 x,y 를 회전시켜준다.
	x -= ptr->dots->x / 2;
	y -= ptr->dots->y / 2;
	*i = x * cos(angle) - y * sin(angle) + ptr->dots->x / 2;
	*j = x * sin(angle) + y * cos(angle) + ptr->dots->y / 2;;
	printf("x is %f y is %f\n", *i, *j);
}
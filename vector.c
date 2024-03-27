/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:15:25 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/27 13:21:34 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vect	make_vect(double cx, double cy, t_ptr *ptr)
{
	double	ox;
	double	oy;
	t_vect	ret;

	ox = ptr->view.x;
	oy = ptr->view.y;
	ret.x = +(cx - ox);
	ret.y = -(cy - oy);
	return (ret);
}

double	vect_size(t_vect A)
{
	return (sqrt(A.x * A.x + A.y * A.y));
}

int	vect_ip(t_vect A, t_vect B)
{
	return (A.x * B.x + A.y * B.y);
}

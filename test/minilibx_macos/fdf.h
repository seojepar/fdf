/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:41:09 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/18 19:17:22 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_ptr{
	void	*mlx;
	void	*win;
	void	*img;
}	t_ptr;

typedef struct s_dot{
	int	cx;
	int	cy;
	int	z;
	int	color;
}	t_dot;

void	ft_switch(int *a, int *b);
void	plot_dot(t_dot d, void *mlx_ptr, void *win_ptr);
void	plot_line_high(t_dot d1, t_dot d2, void *mlx_ptr, void *win_ptr);
void	plot_line_low(t_dot d1, t_dot d2, void *mlx_ptr, void *win_ptr);
void	plot_line(t_dot d1, t_dot d2, t_ptr ptr);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:41:09 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/06 16:11:35 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define INPUT_ERR 0
# define RET_SUC 1
# define RET_ERR 0

typedef struct s_ptr{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		pix; // pixel_bits
	int		line; // line_bytes
	int		end; // endian
	int		x;
	int		y;
}	t_ptr;

typedef struct s_dot{
	int	cx;
	int	cy;
	int	z;
	int	color;
}	t_dot;

char	*ft_substr(char *start, char *end);
int		ft_strlen(char *str);
char	*ft_strcat(char *s1, char *s2);
int		ft_0xatoi(char *str);
int		ft_atoi(char **str);
void	ft_switch(int *a, int *b);

void	draw_dot(t_ptr ptr, t_dot **dots, int x, int y);
void	plot_dot(t_dot d, t_ptr ptr);
void	plot_line_high(t_dot d1, t_dot d2, t_ptr ptr);
void	plot_line_low(t_dot d1, t_dot d2, t_ptr ptr);
void	plot_line(t_dot d1, t_dot d2, t_ptr ptr);
void	img_pixel_put(t_ptr ptr, int x, int y, int color);

char	*ft_strjoin(char *a, char *b);
char	*ft_read(int fd);

#endif
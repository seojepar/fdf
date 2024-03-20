/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:41:09 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/20 10:57:35 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define BUF_SIZE 100000

# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define PGDN 121
# define PGUP 116
# define MINUS 27
# define PLUS 24
# define SCALE 40

# define INPUT_ERR	 	0
# define RET_SUC 		1
# define RET_ERR 		0
# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEMOVE	6
# define ON_MOUSEUP		5
# define ON_DESTROY		17
# define HEIGHT_SCALE	3.5

# define WIN_X 1200
# define WIN_Y 1200

typedef struct s_coord{
	int	cx;
	int	cy;
	int	z;
	int	color;
}	t_coord;

typedef struct s_dots{
	int		x;
	int		y;
	t_coord	**dot;
}	t_dots;

typedef struct s_mouse{
	int	mx;
	int	my;
	int	onoff;
}	t_mouse;

typedef struct s_view{
	int		x;
	int		y;
	t_mouse mouse;
	int		scale;
	float	height;
}	t_view;

typedef struct s_ptr{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	t_dots	*dots;
	t_view	view;
	int		pix;
	int		line;
	int		end;
}	t_ptr;

char	*ft_substr(char *start, char *end);
int		ft_strlen(char *str);
char	*ft_strcat(char *s1, char *s2);
int		ft_0xatoi(char *str);
int		ft_atoi(char **str);
void	ft_switch(int *a, int *b);

void	gen_dots(t_ptr *ptr);
void	plot_coord(t_coord d, t_ptr ptr);
void	plot_line_high(t_coord d1, t_coord d2, t_ptr ptr);
void	plot_line_low(t_coord d1, t_coord d2, t_ptr ptr);
void	plot_line(t_coord d1, t_coord d2, t_ptr ptr);
void	img_pixel_put(t_ptr ptr, int x, int y, int color);

int		get_xy(char	*file, t_dots *info);
char	*ft_strjoin(char *a, char *b);
char	*read_file(int fd);
int		mouse_move(int x, int y, void *param);
void	hooks(t_ptr	ptr);
void	init_mlx(t_ptr *ptr);

int		key_handler(int key, void *arg);
int		mouse_on(int button, int x, int y, void *param);
int		mouse_off(int button, int x, int y, void *param);
int		expose_handler(void *param);
int		ft_close(t_ptr *ptr);
int		mouse_move(int x, int y, void *param);
void	gen_dots(t_ptr *ptr);
t_dots	*get_dots(int fd);
void	save_dots(char *buf, t_dots *info);
int		init_info(t_dots *info);
void	reset_buf(t_ptr ptr);
int		out_of_win(t_coord d1, t_coord d2);

int		div_color(int m, int n, int c1, int c2);
int		gen_color(t_coord d1, t_coord d2, t_coord dc, int flag);
void	error(char *msg, int code);

#endif
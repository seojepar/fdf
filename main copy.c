/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/24 13:01:24 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	error(char *msg, int code)
{
	printf("Error: %s\n", msg);
	exit(code);
}

int	main(int argc, char *argv[])
{
	t_ptr	ptr;

	if (argc != 2)
		return (0);
	ptr.dots = get_dots(open(argv[1], O_RDONLY));
	if (!ptr.dots)
		error("Incorrect file format", 0);
	init_mlx(&ptr);
	gen_dots(&ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 0, 0);
	event_handler(ptr);
	return (0);
}

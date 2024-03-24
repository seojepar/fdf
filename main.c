/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/24 17:05:30 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_ptr	ptr;

	if (argc != 2)
		return (0);
	ptr.dots = store(open(argv[1], O_RDONLY));
	if (!ptr.dots)
		exit(0);
	init(&ptr);
	make_img(&ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 0, 0);
	events(ptr);
	return (0);
}

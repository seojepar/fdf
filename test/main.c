/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/08 16:15:30 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	main(int argc, char *argv[])
{
	// if (argc != 2)
	// 	return (INPUT_ERR);
	t_ptr	ptr;
	ptr.in = get_input(open("./test_maps/42.fdf", O_RDONLY));
	init_mlx(&ptr);
	dots_to_img(&ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, ptr.view.x, ptr.view.y);
	hooks(ptr);
}

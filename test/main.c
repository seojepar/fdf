/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/13 18:16:04 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	error(void)
{
	printf("Error\n");
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_ptr	ptr;

	if (argc != 2)
		error();
	ptr.in = get_input(open(argv[1], O_RDONLY));
	if (!ptr.in)
		error();
	init_mlx(&ptr);
	dots_to_img(&ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 0, 0);
	hooks(ptr);
}

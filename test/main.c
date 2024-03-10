/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/10 16:53:15 by seojepar         ###   ########.fr       */
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

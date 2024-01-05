/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:42:15 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/05 15:43:33 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_x(char **my)
{
	int	x;

	x = 0;
	while (*(my + x))
		x++;
	return (x);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		x_max;
	int		y_max;
	char	**tmp;
	char	*line;

	if (argc != 2)
		return (0);
	// fd = open(argv[1], O_RDONLY);
	y_max = 0;
	x_max = 0;
	printf("Hi");
	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	if (!line)
	// 		break ;
	// 	tmp = ft_split(line, ' ');
	// 	free(line);
	// 	x_max = get_x(tmp);
	// 	free(tmp);
	// 	y_max++;
	// }
	printf("x is %d, y is %d", x_max, y_max);
	// close(fd);
}

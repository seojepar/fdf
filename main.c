/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/09 21:11:40 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_dot{
	int	z;
	int	color;
}	t_dot;

char	*ft_substr(char *start, char *end)
{
	char	*out;
	int		i;

	out = (char *)malloc(end - start + 2);
	if (!out)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		*(out + i) = *(start + i);
		i++;
	}
	*(out + i) = '\0';
	return (out);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
		i++;
	return (i);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*out;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = malloc(len1 + len2 + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		out[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		out[len1 + i] = s2[i];
		i++;
	}
	free(s1);
	free(s2);
	return (out);
}

int	ft_0xatoi(char *str)
{
	int	num;

	num = -1;
	while (*str)
	{
		str++;
		if (!('0' <= *str && *str <= '9'))
			break ;
		if (*str == ',')
		{
			num = 0;
			str += 3;
			break ;
		}
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 16 + *str - '0';
		else if ('A' <= *str && *str <= 'F')
			num = num * 16 + *str - 'A' + 10;
		else
			break ;
		str++;
	}
	return (num);
}

int	ft_atoi(char *str)
{
	int	flag;
	int	num;

	flag = 1;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		flag = -1;
		str++;
	}
	num = 0;
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return (num * flag);
}

int	main(int argc, char *argv[])
{
	int		fd = open(argv[1], O_RDONLY);
	int		nbyte = 1000;
	char	*buf = malloc(nbyte + 1);
	char	*tmp;
	int		x;
	int		y;
	int		sp;

	read(fd, buf, nbyte);
	tmp = buf;
	x = 0;
	y = 0;
	sp = 1;
	while (*buf)
	{
		if (!sp && *buf == ' ' || *buf == '\n')
			x++;
		if (*buf == '\n')
			y++;
		sp = (*buf == ' ');
		buf++;
	}
	if (y != 0)
		x /= y;
	// x and y is done while this
	t_dot	**dots = (t_dot **)malloc(sizeof(t_dot *) * x);
	int	i = 0;
	int	j = 0;
	while (j < x)
		dots[j++] = (t_dot *)malloc(sizeof(t_dot) * y);
	i = 0;
	j = 0;
	sp = 1;
	while (*tmp)
	{
		if (sp && *tmp != ' ' && *tmp != '\n')
		{
			printf("i: %d, j: %d\n", i, j);
			dots[i][j].z = ft_atoi(tmp);
			dots[i][j].color = ft_0xatoi(tmp);
			printf("z: %d, color: %d\n", dots[i][j].z, dots[i][j].color);
			i++;
		}
		if (*tmp == '\n')
		{
			i = 0;
			j++;
		}
		sp = (*tmp == ' ' || *tmp == '\n');
		tmp++;
	}
}
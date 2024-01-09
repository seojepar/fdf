/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/09 18:32:10 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_dot{
	int		z;
	char	*color;
} t_dot

char	*ft_substr(char *start, char *end)
{
	char	*out;
	int		i;

	out = malloc(end - start + 2);
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

int		ft_strlen(char *str)
{
	int	i = 0;

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

int	main(int argc, char *argv[])
{
	int		fd = open(argv[1], O_RDONLY);
	int		nbyte = 1000;
	char	*buf = malloc(nbyte + 1);
	int		x;
	int		y;
	int		sp;

	// 미해결: 버퍼사이즈가 부족한 경우 strcat을 통하여 계속해서 합치는 작업이 필요
	read(fd, buf, nbyte);
	x = 0;
	y = 0;
	sp = 1;
	while(*buf)
	{
		if (!sp && *buf == ' ' || *buf == '\n')
			x++;
		if (*buf == '\n')
			y++;
		sp = (*buf == ' ');
		buf++;
	}
	x /= y;
	printf("x is %d y is %d", x, y);
	/*
	파일을 파싱해서 내가 원하는 포맷대로 저장할 수 있어야 된다.
	문제1: 파일 사이즈가 버퍼 사이즈를 넘어가게 되면? 계속 string을 합쳐서 하나의 string으로 만들어준다!

	1> 하나의 겁나 큰 문자열로 저장하자.
	2> 문자의 개수를 받자. \n의 개수를 세자.
	3> 그만큼 할당을 하자.
	4> split 쓰면서 바로 atoi 적용시켜서 숫자로 저장하자.
	*/
	// 구조체의 배열을 쓰자! point[x][y] 에 z랑, 색깔을 저장하는거야.
}
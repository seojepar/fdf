/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:02:55 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/03/03 18:32:03 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		ft_strlen(char *a)
{
	int	len;

	len = 0;
	while (*(a + len))
		len++;
	return (len);
}

char	*ft_strjoin(char *a, char *b)
{
	int		len;
	char	*out;
	int		i;
	int		j;

	out = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	i = 0;
	while (*(a + i))
	{
		*(out + i) = *(a + i);
		i++;
	}
	j = 0;
	while (*(b + j))
	{
		*(out + i + j) = *(b + j);
		j++;
	}
	return (out);
}

/* 온전히 동작하는 것을 확인
int main()
{
	printf("%s", ft_strjoin("Hello", "Polarbear"));
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:48:00 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/04/13 14:48:33 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

char	*ft_strjoin(char *a, char *b)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (*(a + i))
	{
		*(ret + i) = *(a + i);
		i++;
	}
	j = 0;
	while (*(b + j))
	{
		*(ret + i + j) = *(b + j);
		j++;
	}
	*(ret + i + j) = '\0';
	free(a);
	return (ret);
}

int	ft_0xatoi(char *str)
{
	int	num;

	if (*str != ',')
		return (0xFFFFFF);
	str += 3;
	num = 0;
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			num = num * 16 + *str - '0';
		else if ('A' <= *str && *str <= 'F')
			num = num * 16 + *str - 'A' + 10;
		else if ('a' <= *str && *str <= 'f')
			num = num * 16 + *str - 'a' + 10;
		else
			break ;
		str++;
	}
	return (num);
}

int	ft_atoi(char **str)
{
	int	flag;
	int	num;

	flag = 1;
	if (**str == '+')
		(*str)++;
	if (**str == '-')
	{
		flag = -1;
		(*str)++;
	}
	num = 0;
	while ('0' <= **str && **str <= '9')
	{
		num = num * 10 + **str - '0';
		(*str)++;
	}
	return (num * flag);
}

int	is_blank(char c)
{
	return ((9 <= c && c <= 13) || (c == 32));
}

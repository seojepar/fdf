/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:48:00 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/04/12 13:48:15 by seojeongpar      ###   ########.fr       */
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

int	ft_0xatoi(char *str)
{
	int	num;
	int	len;

	if (*str != ',')
		return (0xFFFFFF);
	str += 3;
	num = 0;
	len = 0;
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
		len++;
		str++;
	}
	num = num << (4 * (6 - len));
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

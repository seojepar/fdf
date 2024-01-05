/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:19:31 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/04 18:26:38 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	num;
	int	buho;

	i = 0;
	num = 0;
	buho = 1;
	while (nptr[i] != '\0')
	{
		if (!((9 <= nptr[i] && nptr[i] <= 13) || (nptr[i] == ' ')))
			break ;
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			buho = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	free(nptr);
	return (num * buho);
}

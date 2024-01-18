/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:48:00 by seojeongpar       #+#    #+#             */
/*   Updated: 2024/01/18 20:48:07 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	if (*str != ',')
		return (-1);
	str++;
	num = 0;
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

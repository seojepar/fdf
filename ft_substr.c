/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:22:48 by seojepar          #+#    #+#             */
/*   Updated: 2024/01/05 14:36:56 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	if (start >= (unsigned int)ft_strlen(s))
	{
		tmp = (char *)malloc(1);
		if (!tmp)
			return (NULL);
		*tmp = 0;
		return (tmp);
	}
	if (ft_strlen(s) - start > len)
		i = len;
	else
		i = ft_strlen(s) - start;
	tmp = (char *)malloc(i + 1);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, s + start, i + 1);
	return (tmp);
}

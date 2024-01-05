/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:30:55 by seojepar          #+#    #+#             */
/*   Updated: 2024/01/05 16:16:54 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
필요한 함수
1. str realloc (str) -> char *반환
2. strchr (str, chr) -> char *반환
3. substr (str, str + i) -> char *반환
0. strlen : 그냥 항상 필요 ->
*/
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s || !(*s))
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_ssubstr(char *start, char *end)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)malloc(end - start + 2);
	if (!tmp)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		tmp[i] = *(start + i);
		i++;
	}
	tmp[i] = '\0';
	free(start);
	return (tmp);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (len == 0 || src == dst)
		return (dst);
	if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (1)
		{
			*((char *)dst + i) = *((char *)src + i);
			if (i == 0)
				break ;
			i--;
		}
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	tmp = (char *)malloc(len);
	if (!tmp)
	{
		free(s1);
		return (NULL);
	}
	ft_memmove(tmp, s1, ft_strlen(s1));
	ft_memmove(tmp + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	i = 0;
	while (i <= BUFFER_SIZE)
		s2[i++] = '\0';
	free(s1);
	return (tmp);
}

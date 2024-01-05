/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:24:14 by seojepar          #+#    #+#             */
/*   Updated: 2024/01/05 14:32:05 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_wordcnt(char const *s, char c)
{
	int		cnt;
	size_t	i;
	int		sp;

	i = 0;
	cnt = 0;
	sp = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && sp)
			cnt++;
		sp = (s[i] == c);
		i++;
	}
	return (cnt);
}

static int	ft_nullcheck(char **tmp, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		if (!tmp[i])
		{
			i = 0;
			while (i < j)
				free(tmp[i++]);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;
	int		len;
	size_t	i;
	size_t	j;

	printf("start");
	tmp = (char **)malloc(sizeof(char *) * (ft_wordcnt(s, c) + 1));
	if (!tmp)
		return (NULL);
	len = 0;
	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if ((s[i] == c || s[i] == '\0') && len)
			tmp[j++] = ft_substr(s, i - len, len);
		len++;
		if (s[i] == c)
			len = 0;
		i++;
	}
	if (!ft_nullcheck(tmp, j))
		return (NULL);
	tmp[j] = NULL;
	return (tmp);
}

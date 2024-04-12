/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeongpark <seojeongpark@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:26:44 by seojepar          #+#    #+#             */
/*   Updated: 2024/04/09 13:05:02 by seojeongpar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	buf_init(char **out, char **buf)
{
	*out = malloc(1);
	if (!*out)
		return (0);
	**out = '\0';
	*buf = malloc(BUF_SIZE + 1);
	if (!*buf)
	{
		free(*out);
		return (0);
	}
	return (1);
}

char	*read_file(int fd)
{
	char	*out;
	char	*buf;
	int		len;

	if (fd < 0)
		return (0);
	buf_init(&out, &buf);
	while (1)
	{
		len = read(fd, buf, BUF_SIZE);
		if (len <= 0)
			break ;
		buf[len] = '\0';
		out = ft_strjoin(out, buf);
		if (!out)
		{
			free(buf);
			return (0);
		}
	}
	free(buf);
	return (out);
}

int is_blank(char c){
	return ((9 <= c && c <= 13) || (c == 32));
}

int get_x(char *file, t_dots *info){
	int	is_sp;
	int	exist_flag;
	int	cnt;

	is_sp = 1;
	exist_flag = 0;
	cnt = 0;
	while (*file)
	{
		if (is_sp && !is_blank(*file))
			cnt++;
		if (exist_flag && *file == '\n'){
			info->x = cnt;
			return (cnt);
		}
		if (!exist_flag && !is_blank(*file))
			exist_flag = 1;
		is_sp = is_blank(*file);
		file++;
	}
	info->x = cnt;
	return (cnt);
}

int	get_xy(char	*file, t_dots *info)
{
	int	is_sp;
	int	row_x;
	int	total_count;

	if (!get_x(file, info))
		return (RET_ERR);
	row_x = 0;
	is_sp = 1;
	total_count = 0;
	while (*file)
	{
		if (is_sp && !((*file == ' ') || (*file == '\n')))
			row_x++;
		if (*file == '\n')
		{
			total_count += row_x;
			if (row_x != info->x)
			{
				free(info);
				return (INPUT_ERR);
			}
			row_x = 0;
		}
		is_sp = ((*file == ' ') || (*file == '\n'));
		file++;
	}
	info->y = total_count / info->x;
	return (RET_SUC);
}

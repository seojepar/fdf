# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

#include "fdf.h"

char	*ft_strjoin(char *a, char *b)
{
	int		len;
	char	*out;
	int		i;
	int		j;

	out = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	// 코딩에서 지금 널가드가 하나도 안되어있다.
	if (!out)
		return (NULL);
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
	*(out + i + j) = '\0';
	free(a);
	return (out);
}

char	*ft_read(int fd)
{
	char	*out;
	char	*buf;
	int		n = 100000;

	out = malloc(1);
	*out = '\0';
	// read 함수 사용하기 전에 초기화 안해서 쓰레기값까지 다 들어갔었다.
	buf = malloc(n);
	int i = 0;
	while (read(fd, buf, n) > 0)
	{
		out = ft_strjoin(out, buf);
		free(buf);
		buf = malloc(n);
	}
	free(buf);
	return (out);
}

// int	main(int argc, char *argv[])
// {
// 	char	*buf = ft_read(open(argv[1], O_RDONLY));
// 	printf("This is the buffer:\n%s", buf);
// }
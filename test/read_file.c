# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

#include "fdf.h"

// a=out, b=buf
char	*ft_strjoin(char *a, char *b)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	ret = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	// 코딩에서 지금 널가드가 하나도 안되어있다.
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

char	*ft_read(int fd)
{
	char	*out;
	char	*buf;
	int		n = 100000;

	out = malloc(1);
	*out = '\0';
	// read 함수 사용하기 전에 초기화 안해서 쓰레기값까지 다 들어갔었다.
	buf = malloc(n + 1);
	while (1)
	{
		int len = read(fd, buf, n);
		if (len <= 0)
			break;
		// read는 널을 보장해주지 않는다 - sgang
		buf[len] = '\0';
		out = ft_strjoin(out, buf);
		// free(buf);
		// buf = malloc(n);
	}
	free(buf);
	return (out);
}

// int	main(int argc, char *argv[])
// {
// 	char	*buf = ft_read(open(argv[1], O_RDONLY));
// 	printf("This is the buffer:\n%s", buf);
// }
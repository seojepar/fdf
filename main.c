#include <stdio.h>

int main()
{
	int	a[5] = {1, 2, 3, 4, 5};
	int	*ptr = a;

	printf("%d\n", *(ptr));
	printf("%d\n", *(ptr + 1));
	printf("%d\n", *(ptr + 2));
	printf("%d\n", *(ptr + 3));
	printf("%d\n", *(ptr + 4));

	int b[4][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
	// 에러: int *pptr = b;
	int	*pptr = &(b[0][0]);
	printf("%d\n", *pptr);
	printf("%d\n", *(pptr + 1));
	printf("%d\n", *(pptr + 2));
	printf("%d\n", *(pptr + 3));
	printf("%d\n", *(pptr + 4));
	// 결론: 2차원 배열도 단일포인터를 증가시키는 방법을 통해 접근할 수 있다.
}
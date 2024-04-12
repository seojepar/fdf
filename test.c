#include <stdio.h>

int main(){
	printf("Hex is %s\n", "810202");
	int color = 0xFF0000;
	int buffer[4];
	buffer[0] = (color) & 0xFF;
	buffer[1] = (color >> 8) & 0xFF;
	buffer[2] = (color >> 16) & 0xFF;
	buffer[3] = (color >> 24);
	for(int i=0;i<4;i++)
		printf("buffer[%d] is %d\n", i, buffer[i]);
}
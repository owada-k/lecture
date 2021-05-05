#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int a, b, c;

	if (argc != 3) {
		printf("%s a b\n", argv[0]);
		printf(" This program add a and b.\n");
		printf(" a and b should be number.\n");
		return -1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = a + b;

	printf("%d + %d = %d\n", a,b,c) ;
}

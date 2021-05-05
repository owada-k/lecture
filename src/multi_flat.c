#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int	a, b, c;
	int	i;

	if (argc != 3) {
		printf("Usage: %s a b\n", argv[0]);
		printf(" This program multiply a and b.\n");
		printf(" a and b should be number.\n");
		return -1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	c = 0;
	for (i = 0 ; i < b; i++) {
		c += a;
	}

	printf("%d x %d = %d\n", a,b,c) ;


	c = 0;
	for (i = 0 ; i < a; i++) {
		c += a;
	}
	for (i = 0 ; i < b; i++) {
		c += b;
	}

	printf("%d^2 x %d^2 = %d\n", a,b,c) ;

	return 0;
}


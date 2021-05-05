#include <stdio.h>
#include <stdlib.h>

int show_usage(char *name);
int multi(int int1, int int2);
int square(int int1);

int main(int argc, char** argv)
{
	int	a, b, c;

	if (argc != 3) {
		show_usage(argv[0]);
		return -1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	c = square(a) + square(b);

	printf("%d^2 x %d^2 = %d\n", a,b,c) ;

	return 0;
}

int show_usage(char *name)
{
	printf("Usage: %s a b\n", name);
	printf(" This program add square of a and b.\n");
	printf(" a and b should be integer.\n");

	return 0;
}

int multi(int int1, int int2)
{
	int	i;
	int	result;

	result = 0;
	for (i = 0 ; i < int2; i++) {
		result += int1;
	}

	return result;
}

int square(int int1)
{
	int	result;

	result = multi(int1, int1);

	return result;
}

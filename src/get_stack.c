#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	ITERATION	4

#define	MEM_UNIT	(1024 * 1024)
#define	MEM_SIZE	(MEM_UNIT * 16 / ITERATION)

#include "set_mem.h"


int get_stack(char xor_data)
{
	char	data[MEM_SIZE];

	set_data(xor_data, MEM_SIZE, data, MEM_MSG_FLAG_START_END | MEM_MSG_FLAG_AT_QUARTER);

	return 0;
}

int main(int argc, char** argv)
{
	printf("[%d] %s begin\n", getpid(), CMD);
	system(CMD);

	printf("Iteration 1\n");
	get_stack(0x00);

	printf("Iteration 2\n");
	get_stack(0x0f);

	printf("Iteration 3\n");
	get_stack(0xf0);

	printf("Iteration 4\n");
	get_stack(0xff);

	printf("[%d] %s end\n", getpid(), CMD);
	system(CMD);

	printf("done!\n");
}


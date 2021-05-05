#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	ITERATION	30

#define	MEM_UNIT	(1024 * 1024 / 4)
#define	MEM_SIZE	(MEM_UNIT)

#define	MEM_MSG_FLAG	(0)

#include "set_mem.h"


int get_stack_recursive(int recursive_count)
{
	char	data[MEM_SIZE];
	char	xor_data[] = {0x00, 0x0f, 0xf0, 0xff};
	int	msg_flag = MEM_MSG_FLAG;

	if (recursive_count == 0) {
		return 0;
	}

	if (msg_flag & MEM_MSG_FLAG_START_END) {
		printf("Iteraton %d %s enter\n", ITERATION + 1 - recursive_count, CMD);
		system(CMD);
	}

	if (msg_flag & MEM_MSG_FLAG_AT_QUARTER) {
		printf("[%d] %s begin set_data iteration %d\n", getpid(), CMD, ITERATION + 1 - recursive_count);
		system(CMD);
	}

	set_data(xor_data[3 - ((recursive_count - 1) % 4)], MEM_SIZE, data, msg_flag);

	if (msg_flag & MEM_MSG_FLAG_AT_QUARTER) {
		printf("[%d] %s end set_data iteration %d\n", getpid(), CMD, ITERATION + 1 - recursive_count);
		system(CMD);
	}

	get_stack_recursive(recursive_count - 1);

	if (msg_flag & MEM_MSG_FLAG_START_END) {
		printf("Iteraton %d %s return\n", ITERATION + 1 - recursive_count, CMD);
		system(CMD);
	}
	return 0;
}

int main(int argc, char** argv)
{
	if (MEM_MSG_FLAG & MEM_MSG_FLAG_START_END) {
		printf("[%d] %s begin\n", getpid(), CMD);
		system(CMD);
	}

	get_stack_recursive(ITERATION);

	if (MEM_MSG_FLAG & MEM_MSG_FLAG_START_END) {
		printf("[%d] %s end\n", getpid(), CMD);
		system(CMD);
	}
	printf("done!\n");
}


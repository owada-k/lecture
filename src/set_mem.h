#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#ifndef MEM_UNIT
#define	MEM_UNIT	(1024 * 1024)
#endif

#ifndef MEM_SIZE
#define	MEM_SIZE	(MEM_UNIT * 1024)
#endif

#define	MEM_MSG_FLAG_START_END	0x01
#define	MEM_MSG_FLAG_AT_UNIT	0x02
#define	MEM_MSG_FLAG_AT_QUARTER	0x04

int set_data(char xor_data, int size, char data[size], int msg_flag);

#define	CMD	"free -tm"

int set_data(char xor_data, int size, char data[size], int msg_flag)
{
	int	i; 

	if (msg_flag & MEM_MSG_FLAG_START_END) {
		printf("[%d] %s begin\n", getpid(), CMD);
		system(CMD);
	}

	for (i = 0; i < size; i++) {
		if (((i % MEM_UNIT) == 0) && (msg_flag & MEM_MSG_FLAG_AT_UNIT)) {
			printf("[%d] data[%d]\n", getpid(), i);
		}

		if (((i % (size / 4)) == 0) && (msg_flag & MEM_MSG_FLAG_AT_QUARTER)) {
			printf("[%d] %s data[%d]\n", getpid(), CMD, i);
			system(CMD);
		}

		data[i] = i % (0x100 ^ sizeof(char));
		data[i] ^= xor_data;
	} 

	if (msg_flag & MEM_MSG_FLAG_START_END) {
		printf("[%d] %s end\n", getpid(), CMD);
		system(CMD);
	}

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define	MEM_UNIT	(1024 * 1024)
#define	MEM_SIZE	(MEM_UNIT * 1024)

#include "set_mem.h"

char	data[MEM_SIZE];

int main(int argc, char** argv)
{
	struct timespec start_time, end_time;
	clock_t		start_clock, end_clock;
	int		msg_flag;

	if (argc == 2) {
		msg_flag = atoi(argv[1]);
	} else {
		msg_flag = MEM_MSG_FLAG_START_END | MEM_MSG_FLAG_AT_QUARTER;
	}

	clock_gettime(CLOCK_REALTIME, &start_time);
	start_clock = clock();

	set_data(0x00, MEM_SIZE, data, msg_flag);

	clock_gettime(CLOCK_REALTIME, &end_time);
	end_clock = clock();

	printf("[%d] done! RealTime = %ld, CPU time = %d\n", getpid(), end_time.tv_sec - start_time.tv_sec, (int)((end_clock - start_clock) / CLOCKS_PER_SEC));
}

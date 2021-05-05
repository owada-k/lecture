#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <wait.h>


#define	MEM_UNIT	(1024 * 1024)
#define	MEM_SIZE	(MEM_UNIT * 1024)
#define	MEM_MSG_FLAG	MEM_MSG_FLAG_START_END

#include "set_mem.h"

char	data[MEM_SIZE];

int main(int argc, char** argv)
{
        pid_t   pid;
	int	status;

	/* Initialize */
	set_data(0x00, MEM_SIZE, data, MEM_MSG_FLAG);

        pid = fork();
        if (pid < 0) {
                return -1;
        }

	if (pid == 0) {
		/* this is child process */
		/* reinit again */
		set_data(0xff, MEM_SIZE, data, MEM_MSG_FLAG);
	} else {
		wait(&status);
	}

	printf("[%d] done!: &data = %p, data[0] = 0x%02x\n", getpid(), &data, (unsigned char) data[0]);
}


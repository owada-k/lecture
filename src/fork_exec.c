#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <wait.h>

#define	PROG1 "./hello_world"
#define	PROG2 "./a_plus_b"

int main(int argc, char** argv)
{
	pid_t	pid, pid1, pid2;


	pid = fork();
	if (pid < 0) {
		return -1;
	}

	if (pid == 0) {
		if (execl(PROG1, PROG1, (char *)NULL) < 0) {
			perror(strerror(errno));
			return -2;
		}
	}

	pid1 = pid;
	

	pid = fork();
	if (pid < 0) {
		return -1;
	}

	if (pid == 0) {
		if (execl(PROG2, PROG2, (char *)NULL) < 0) {
			perror(strerror(errno));
			return -2;
		}
	}

	pid2 = pid;


	printf("Parent(%d), child1(%d), child2(%d)\n", getpid(), pid1, pid2);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}

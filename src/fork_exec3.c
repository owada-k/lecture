#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <wait.h>

#define	PROG1	 	"./get_mem"
#define	PROG1_ARGV	 "0"
#define	PROG2		PROG1
#define	PROG2_ARGV	PROG1_ARGV

pid_t fork_exec(char *prog, char *prog_argv)
{
	pid_t	pid;
	cpu_set_t	cpu_set;

	CPU_ZERO(&cpu_set);
	CPU_SET(0, &cpu_set);

	pid = fork();
	if (pid < 0) {
		return -1;
	}

	if (pid == 0) {
		if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set) != 0) {
			return -1;
		}

		if (execl(prog, prog, prog_argv, (char *)NULL) < 0) {
			perror(strerror(errno));
			return -2;
		}
	}

	return pid;
}

int main(int argc, char** argv)
{
	pid_t	pid1, pid2;


	pid1 = fork_exec(PROG1, PROG1_ARGV);
	
	pid2 = fork_exec(PROG2, PROG2_ARGV);


	setpriority(PRIO_PROCESS, pid1, 10);

	printf("Parent(%d), child1(%d), child2(%d)\n", getpid(), pid1, pid2);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}

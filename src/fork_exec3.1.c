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

pid_t fork_exec(char *prog, char *prog_argv, int policy, int priority)
{
	pid_t	pid;
	cpu_set_t	cpu_set;
	struct sched_param	param;

	CPU_ZERO(&cpu_set);
	CPU_SET(0, &cpu_set);

	param.sched_priority = priority;

	pid = fork();
	if (pid < 0) {
		return -1;
	}

	if (pid == 0) {
		if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set) != 0) {
			return -1;
		}

		if (sched_setscheduler(pid, policy, &param) != 0) {
			perror(strerror(errno));
			return -3;
		}
		printf("[%d] ", getpid());
		switch (policy) {
		case SCHED_FIFO:
			printf("sched policy SCHED_FIFO (prio = %d)\n", priority);
			break;
		case SCHED_RR:
			printf("sched policy SCHED_RR (prio = %d)\n", priority);
			break;
		case SCHED_OTHER:
			printf("sched policy SCHED_OTHER (prio = %d)\n", priority);
			break;
		default:
			printf("sched policy %d (prio = %d)\n", policy, priority);
			break;
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
	struct sched_param	param;

	param.sched_priority = 99;
	if (sched_setscheduler(0, SCHED_FIFO, &param) != 0) {
		perror(strerror(errno));
		return -3;
	}


	pid1 = fork_exec(PROG1, PROG1_ARGV, SCHED_FIFO, 1);
	pid2 = fork_exec(PROG2, PROG2_ARGV, SCHED_RR, 2);
	pid2 = fork_exec(PROG1, PROG1_ARGV, SCHED_FIFO, 2);
	pid2 = fork_exec(PROG1, PROG1_ARGV, SCHED_FIFO, 3);
	pid2 = fork_exec(PROG2, PROG2_ARGV, SCHED_RR, 2);


//	setpriority(PRIO_PROCESS, pid1, 10);

	printf("Parent(%d), child1(%d), child2(%d)\n", getpid(), pid1, pid2);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}

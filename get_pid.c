#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid;
	pid = getpid();  // Get the PID of the current process
	printf("PID: %d\n", pid);

	return 0;
}

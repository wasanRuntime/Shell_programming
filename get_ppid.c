#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t ppid;
	ppid = getppid();  // Get the PPID of the current process
	printf("PPID: %d\n", ppid);

	return 0;
}

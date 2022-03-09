#include <stdlib.h>
#include <stdio.h>
#include <sys/env.h>
#include <sys/spawn.h>

void system(char* command) {
	task_t* task = (task_t*) env(ENV_GET_TASK);

	if (task->system_method == NULL) {
		printf("System method not set.\n");
		abort();
	}

	task->system_method(command);
}
#include <stdlib.h>
#include <sys/env.h>
#include <stdio.h>
#include <errno.h>

#include <buildin/sighandler.h>
#include <buildin/thread.h>

extern int main(int argc, char* argv[], char* envp[]);

void _start() {
	for (int i = 0; i < 32; i++) {
		env_set2(ENV_SIGHANDLER, i, __libc_sighandler);
	}
	
	__libc_init_alloc();
	__libc_init_stdio();
	__libc_init_childs_list();

	env_set(ENV_ERRNO, &__errno);

	char** argv = env(ENV_ARGV);
	char** envp = env(ENV_ENVP);
	int argc = 0;

	while(argv[argc] != NULL) {
		argc++;
	}

	int return_code = main(argc, argv, envp);

	exit(return_code);
}

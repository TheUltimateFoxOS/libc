#include <stdlib.h>
#include <sys/env.h>
#include <string.h>

char* getenv(const char* name) {
	size_t name_len = strlen((char*) name);

	char** envp = env(ENV_ENVP);

	for (size_t i = 0; envp[i] != NULL; i++) {
		if (strncmp(name, envp[i], name_len) == 0) {
			// Assume vars have the format VAR=VALUE.
			return envp[i] + name_len + 1;
		}
	}

    return NULL;
}
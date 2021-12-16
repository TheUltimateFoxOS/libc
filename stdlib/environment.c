#include <stdlib.h>
#include <sys/env.h>
#include <string.h>
#include <stdio.h>

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

void compute_dot_dot(char* path, char* output);

void resolve(char* path, char* output) {
	char* cwd = (char*) env(ENV_GET_CWD);
	memcpy(output, cwd, strlen(cwd));

	char tmp[256];
	memset(tmp, 0, sizeof(tmp));

	strcpy(tmp, path);

	char* colon = strchr(tmp, ':');
	if (colon == NULL) {
		if (output[strlen(output) - 1] == '/') {
			output[strlen(output) - 1] = '\0';
		}

		if (tmp[0] == '/') {
			printf("Unsupported path: '%s'\n", tmp);
			return;
		}

		if (tmp[strlen(tmp) - 1] == '/') {
			tmp[strlen(tmp) - 1] = '\0';
		}

		strcat(output, "/");
		strcat(output, tmp);
	} else {
		memset(output, 0, sizeof(output));
		strcpy(output, tmp);
	}

	char compute_dot_dot_path[256];
	memset(compute_dot_dot_path, 0, sizeof(compute_dot_dot_path));
	strcpy(compute_dot_dot_path, output);

	compute_dot_dot(compute_dot_dot_path, output);
}

void compute_dot_dot(char* path, char* output) {
	// example input fat32_0:/bin/..
	// example output fat32_0:/
	// example input fat32_0:/efi/foxos/../boot
	// example output fat32_0:/efi/foxos/boot

	char* path_segments[256];
	int path_segments_count = 0;
	memset(path_segments, 0, sizeof(path_segments));

	int path_len = strlen(path);
	for (int i = 0; i < path_len; i++) {
		if (path[i] == '/') {
			path[i] = '\0';
			path_segments[path_segments_count++] = &path[i + 1];
		}
	}

	

	for (int i = 0; i < path_segments_count; i++) {
		if (strcmp(path_segments[i], "..") == 0) {
			if (i == 0) {
				printf("Unsupported path: '%s'\n", path);
				return;
			}

			int del_idx = i - 1;
			while(del_idx >= 0 && path_segments[del_idx] == NULL) {
				del_idx--;
			}

			path_segments[del_idx] = NULL;
			path_segments[i] = NULL;
		}
	}

	memset(output, 0, 256);
	strcpy(output, strtok(path, "/"));

	for (int i = 0; i < path_segments_count; i++) {
		if (path_segments[i] != NULL) {
			strcat(output, "/");
			strcat(output, path_segments[i]);
		}
	}
}
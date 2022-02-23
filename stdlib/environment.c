#include <stdlib.h>
#include <sys/env.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <sys/dir_at.h>

char* getenv(const char* name) {

	size_t name_len = strlen((char*) name);

	char** envp = env(ENV_ENVP);

	for (size_t i = 0; envp[i] != NULL; i++) {
		if (strncmp(name, envp[i], name_len) == 0) {
			// Assume vars have the format VAR=VALUE.
			if (envp[i][name_len] == '=') {
				return envp[i] + name_len + 1;
			} else {
				return NULL;
			}
		}
	}

    return NULL;
}

bool compute_dot_dot(char* path, char* output);

bool exists_recursive(char* input, int current_slash) {
	// printf("exists_recursive: %s\n", input);
	char path_to_check[256];
	char file_or_dir_to_check[256];

	memset(path_to_check, 0, sizeof(path_to_check));
	memset(file_or_dir_to_check, 0, sizeof(file_or_dir_to_check));

	int index_of_slash_in_string = 0;
	int current_slash_idx = current_slash;
	while (current_slash_idx != -1 && index_of_slash_in_string < strlen(input)) {
		index_of_slash_in_string++;
		if (input[index_of_slash_in_string] == '/') {
			current_slash_idx--;
		}
	}

	for (int i = 0; i < index_of_slash_in_string; i++) {
		path_to_check[i] = input[i];
	}

	for (int i = index_of_slash_in_string + 1; i < strlen(input); i++) {
		file_or_dir_to_check[i - index_of_slash_in_string - 1] = input[i];
	}

	for (int i = 0; i < strlen(file_or_dir_to_check); i++) {
		if (file_or_dir_to_check[i] == '/') {
			file_or_dir_to_check[i] = '\0';
			break;
		}
	}

	// printf("path_to_check: %s\n", path_to_check);
	// printf("file_or_dir_to_check: %s\n", file_or_dir_to_check);

	if (file_or_dir_to_check[0] == '\0') {
		return true;
	}

	dir_t dir = dir_at(0, path_to_check);
	do {
		for (int i = 0; i < strlen(dir.name); i++) {
			if (dir.name[i] >= 'A' && dir.name[i] <= 'Z') {
				dir.name[i] = dir.name[i] + 32;
			}
		}

		for (int i = 0; i < strlen(file_or_dir_to_check); i++) {
			if (file_or_dir_to_check[i] >= 'A' && file_or_dir_to_check[i] <= 'Z') {
				file_or_dir_to_check[i] = file_or_dir_to_check[i] + 32;
			}
		}

		// printf("dir.name: %s\n", dir.name);

		if (strcmp(dir.name, file_or_dir_to_check) == 0) {
			return exists_recursive(input, current_slash + 1);
		}

		dir = dir_at(dir.idx + 1, path_to_check);
	} while (!dir.is_none);

	return false;
}

bool resolve_check(char* path, char* output, bool check_child) {
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
			memset(output, 0, sizeof(output));
			strcpy(output, strtok(cwd, ":"));
			strcat(output, ":");
			strcat(output, tmp);
		} else {
			if (tmp[strlen(tmp) - 1] == '/') {
				tmp[strlen(tmp) - 1] = '\0';
			}

			strcat(output, "/");
			strcat(output, tmp);
		}
	} else {
		memset(output, 0, sizeof(output));
		strcpy(output, tmp);
		if (output[strlen(output) - 1] == ':') {
			strcat(output, "/");
		}
	}

	char compute_dot_dot_path[256];
	memset(compute_dot_dot_path, 0, sizeof(compute_dot_dot_path));
	strcpy(compute_dot_dot_path, output);

	bool out = compute_dot_dot(compute_dot_dot_path, output);
	if (!out) {
		return false;
	}
	
	if (output[strlen(output) - 1] == ':') {
		strcat(output, "/");
	}


	// #warning Should check to see if file/dir exists (take into account check_child, for new files).
	return exists_recursive(output, 0);
}

bool resolve(char* path, char* output) {
	return resolve_check(path, output, true);
}

bool compute_dot_dot(char* path, char* output) {
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
				return false;
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

	return true;
}
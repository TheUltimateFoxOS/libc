#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/touch.h>
#include <sys/write.h>
#include <sys/read.h>
#include <sys/open.h>
#include <sys/close.h>
#include <sys/get_file_size.h>
#include <sys/delete.h>
#include <sys/delete_dir.h>
#include <sys/dir_at.h>

struct file_t* stdout;
struct file_t* stdin;
struct file_t* stderr;

int fclose(FILE* stream) {
	close(stream->inner_fd);
	free(stream);
}

int fflush(FILE *stream) {
	write(STDERR, "fflush not implemented\n", 24, 0);
	return 0;
}

FILE *fopen(const char *filename, const char *mode) {
	char filename_full[256];
	memset(filename_full, 0, 256);
	bool exists = resolve((char*) filename, filename_full);

	if (!exists && (strcmp((char*) mode, "w") == 0 || strcmp((char*) mode, "w+") == 0 || strcmp((char*) mode, "wb") == 0)) {
		touch(filename_full);
	}

	int fd = open(filename_full);
	if (fd < 0) {
		return NULL;
	}

	FILE *file = malloc(sizeof(FILE));
	file->inner_fd = fd;
	file->size = get_file_size(fd);
	file->pos = 0;

	return file;
}

FILE *freopen(const char *filename, const char *mode, FILE *stream) {
	fclose(stream);
	return fopen(filename, mode);
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t total = size * nmemb;
	
	read(stream->inner_fd, ptr, total, stream->pos);

	stream->pos += total;
	return 1;
}

int fseek(FILE *stream, long offset, int whence) {
	switch (whence) {
		case SEEK_SET:
			{
				stream->pos = offset;
			}
			break;
		case SEEK_CUR:
			{
				stream->pos += offset;
			}
			break;
		case SEEK_END:
			{
				stream->pos = stream->size + offset;
			}
			break;
	}

	return 0;
}

long ftell(FILE *stream) {
	return stream->pos;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	int total = size * nmemb;
	
	write(stream->inner_fd, ptr, total, stream->pos);

	stream->pos += total;
	return 1;
}

int fprintf(FILE *stream, const char *format, ...) {
	va_list args;
	int i;
	char buf[1024];

	va_start(args, format);
	i = vsprintf(buf, format, args);
	va_end(args);

	write(stream->inner_fd, buf, i, stream->pos);

	stream->pos += i;
	return i;
}

int fputs(const char *s, FILE *stream) {
	write(stream->inner_fd, s, strlen((char*) s), stream->pos);

	stream->pos += strlen((char*) s);
	return 0;
}

int fputc(int c, FILE *stream) {
	write(stream->inner_fd, &c, 1, stream->pos);

	stream->pos += 1;
	return 0;
}

int fgetc(FILE *stream) {
	char c;
	read(stream->inner_fd, &c, 1, stream->pos);

	stream->pos += 1;
	return c;
}

char *fgets(char *s, int size, FILE *stream) {
	int i = 0;
	while (i < size) {
		char c = fgetc(stream);
		if (c == '\n') {
			s[i] = c;
			i++;
			break;
		}
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return s;
}

int ferror(FILE *stream) {
	return 0;
}


void __libc_init_stdio() {
	stdout = malloc(sizeof(struct file_t));
	memset(stdout, 0, sizeof(struct file_t));
	stdout->inner_fd = STDOUT;

	stdin = malloc(sizeof(struct file_t));
	memset(stdin, 0, sizeof(struct file_t));
	stdin->inner_fd = STDIN;

	stderr = malloc(sizeof(struct file_t));
	memset(stderr, 0, sizeof(struct file_t));
	stderr->inner_fd = STDERR;
}

int feof(FILE* stream) {
	if (stream->pos >= stream->size) {
		return 1;
	} else {
		return 0;
	}
}

int remove(const char *filename) {
	char parent_dir[MAX_DIR_NAME_LENGTH]; //Copy of filename
	memset(parent_dir, 0, MAX_DIR_NAME_LENGTH);
	strcpy(parent_dir, filename);

	char* last_slash = strrchr(parent_dir, '/');
	if (last_slash == NULL) {
		return -1;
	}
	char* child_name = last_slash + 1;

	parent_dir[last_slash - parent_dir] = 0; //Cut off the child name

	int file_type = 0; //Get the file type: 0 = file, 1 = directory
	dir_t dir = dir_at(0, parent_dir);
	while (dir.is_none != true) {
		if (strcmp(dir.name, child_name) == 0) {
			if (dir.type == ENTRY_FILE) {
				file_type = 1;
			} else if (dir.type == ENTRY_DIR) {
				file_type = 2;
			}
			break;
		}
		dir = dir_at(dir.idx + 1, parent_dir);
	}

	if (file_type == 1) { //Delete the file
		int fd = open((char*) filename);
		if (fd == -1) {
			return -1;
		}

		delete_(fd);
	} else if (file_type == 2) { //Delete the directory
		delete_dir((char*) filename);
	} else {
		return -1;
	}
	
	bool did_find = false; //Did we actually delete the file?
	dir = dir_at(0, parent_dir);
	while (dir.is_none != true) {
		if (strcmp(dir.name, child_name) == 0) {
			did_find = true;
		}
		dir = dir_at(dir.idx + 1, parent_dir);
	}

	if (!did_find) {
		return 0;
	} else {
		return -1;
	}
}

void rewind(FILE *stream) {
	stream->pos = 0;
}
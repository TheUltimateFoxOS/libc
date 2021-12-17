#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/write.h>
#include <sys/read.h>
#include <sys/open.h>
#include <sys/close.h>
#include <sys/get_file_size.h>

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
	resolve((char*) filename, filename_full);



	int fd = open(filename);
	if (fd < 0) {
		return NULL;
	}

	FILE *file = malloc(sizeof(FILE));
	file->inner_fd = fd;
	file->size = get_file_size(fd);
	file->pos = 0;

	return file;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {

	size_t total = size * nmemb;
	
	read(stream->inner_fd, ptr, total, stream->pos);

	stream->pos += total;
	return total;
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

	size_t total = size * nmemb;
	
	write(stream->inner_fd, ptr, total, stream->pos);

	stream->pos += total;
	return total;
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

	stream->pos += strlen(s);
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
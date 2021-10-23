#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/open.h>
#include <sys/close.h>
#include <sys/write.h>
#include <sys/read.h>

#include <sys/seek_set.h>
#include <sys/seek_get.h>

FILE *fopen(const char *filename, const char *mode) {
	FILE* fp = (FILE*) malloc(sizeof(FILE));
	memset(fp, 0, sizeof(FILE));

	for (int i = 0; i < 3; i++) {
		if (mode[i] == 'r') {
			fp->is_readable = 1;
		} else if (mode[i] == 'w') {
			fp->is_writable = 1;
		} else if (mode[i] == 'a') {
			abort();
		}
	}

	int fd = open(filename, mode);

	fp->inner_fd = fd;

	return fp;
}

int fclose(FILE* stream) {
	close(stream->inner_fd);
	free(stream);
	return 0;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	if (!stream->is_writable) {
		return 0;
	}

	// check if buffer is full (defined as FILE_BUFFER_SIZE)
	if (stream->buffer_i > FILE_BUFFER_SIZE) {
		// flush buffer
		fflush(stream);
	} else {
		if (stream->buffer_i + size * nmemb > FILE_BUFFER_SIZE) {
			// buffer is too small
			fflush(stream);
			write(stream->inner_fd, ptr, size * nmemb);
		} else {
			// copy data to buffer
			memcpy(stream->buffer + stream->buffer_i, ptr, size * nmemb);
			stream->buffer_i += size * nmemb;
		}
	}

	return nmemb;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	if (!stream->is_readable) {
		return 0;
	}

	if (stream->buffer_i != 0) {
		fflush(stream);
	}

	read(stream->inner_fd, ptr, size * nmemb);

	return nmemb;
}

int fflush(FILE *stream) {
	if (!stream->is_writable) {
		return 0;
	}

	if (stream->buffer_i > 0) {
		write(stream->inner_fd, stream->buffer, stream->buffer_i);
		stream->buffer_i = 0;
	}

	return 0;
}

int fseek(FILE *stream, long offset, int whence) {
	if (!stream->is_readable) {
		return -1;
	}

	seek_set(stream->inner_fd, offset, whence);

	return 0;
}

long ftell(FILE *stream) {
	if (!stream->is_readable) {
		return -1;
	}

	return seek_get(stream->inner_fd);
}
#include <stdlib.h>
#include <unistd.h>
#include <err.h>

#define BUFFER_SIZE 512

void rewrite(int fd, const void *buf, size_t count)
{
	int left = count;
	void* p_buf = buf;
	do {
		int n_written = write(fd, buf, count);
		if (n_written == -1) {
			errx(-1, "write()\n");
		}
		p_buf += n_written;
		left -= n_written;
	} while (left > 0);
}

void echo(int fd_in, int fd_out)
{
	char buf[BUFFER_SIZE];
	int n_read = 1;
	do {
		n_read = read(fd_in, buf, BUFFER_SIZE);
		if (n_read == -1) {
			errx(-1, "read()\n");
		}
		rewrite(fd_out, buf, n_read);
	} while (n_read > 0);
}


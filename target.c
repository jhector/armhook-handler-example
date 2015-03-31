#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int written = 0;

void __attribute__((noinline))get_value(void *data, unsigned int *value)
{
	int fd = open("/dev/urandom", O_RDONLY);	

	if (fd < 0) {
		*value = 0x0;
		return;
	}

	read(fd, value, sizeof(*value));
	
	written = 1;

	close(fd);
	return;
}

int main(int argc, char *argv[])
{
	char dummy;
	unsigned int value = 0;

	printf("pid: %d\n", getpid());
	printf("&value: %p\n", &value);
	printf("&get_value: %p\n", &get_value);

	get_value(NULL, &value);
	printf("value: 0x%08x\n", value);

	read(0, &dummy, 1);

	get_value(NULL, &value);
	if (written) {
		printf("value: 0x%08x\n", value);
	} else {
		printf("something is not right\n");
	}

	return 0;
}

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

extern	int errno;

int main()
{
	int fd = open("text.txt", O_RDONLY | O_CREAT);

	printf("fd = %d\n", fd);

	if (fd == -1)
	{
		printf("error number %d\n", errno);
		perror("Program");
	}
	return (0);	
}

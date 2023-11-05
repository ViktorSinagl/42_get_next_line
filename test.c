#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <stdio.h>

int BUFFER_SIZE = 10;
char *BUFF_TST[20];

char *get_next_line(int fd)
{
		
	if (fd < 0)
		return (NULL);
	
}

int main(void)
{
	int fd = open("txt",O_RDONLY);
	char *a = get_next_line(fd);
	printf("%s\n",a)	;
	return (0);
}

#include "get_next_line.h"


int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	(void)argc;
	if (argc < 2)
		argv[1] = "tests/43_with_nl";
	fd = open((argv[1]), O_RDONLY);
	while (i < 2) 
	{
		line = get_next_line(fd);
		printf("-->%s", line);
		free(line);
		i++;
	}
}

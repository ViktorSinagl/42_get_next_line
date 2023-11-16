
#include "get_next_line.h"


int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	(void)argc;
	fd = open((argv[1]), O_RDONLY);
	while (i < 35)
	{
		line = (char *)malloc(sizeof(*line) * 1);
		line = get_next_line(fd);
		printf("-->%s", line);
		free(line);
		i++;
	}
}
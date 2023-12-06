#include "get_next_line.h"

int		main()//int argc , char **argv)
{
	int		fd[3];
	char		*inputs[3];
	char	*line;
	int		i;

	i = 0;
	//if (argc < 2)
	inputs[0] = ".tests/limits7";
	inputs[1] = ".tests/41_with_nl";
	inputs[2] = ".tests/yesterday";
	fd[0] = open((inputs[0]), O_RDONLY);
	fd[1] = open((inputs[1]), O_RDONLY);
	fd[2] = open((inputs[2]), O_RDONLY);
	while (i < 20) 
	{
		if (i % 3 == 0)	
		{
			line = get_next_line(fd[2]);
			printf("fd: %i-->%s\n",fd[2], line);
			free(line);
			i++;
		}
		else if (i % 2 == 0)	
		{
			line = get_next_line(fd[1]);
			printf("fd: %i-->%s\n",fd[1], line);
			free(line);
			i++;
		}
		else	
		{
			line = get_next_line(fd[0]);
			printf("fd: %i-->%s\n",fd[0], line);
			free(line);
			i++;
		}
	}
}

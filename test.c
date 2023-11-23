
#include "get_next_line.h"


int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	(void)argc;
	if (argc < 2)
		argv[1] = "readtext";
	fd = open((argv[1]), O_RDONLY);
	while (i < 2) 
	{
		line = get_next_line(fd);
		printf("-->%s", line);
		free(line);
		i++;
	}
}


//storage:

// char	*read_newline(int fd, char *buff, char **cursor, char *buff_read)
// {
// 	ssize_t		read_err;
// 	char		*tmp;

// 	while(1)
// 	{
// 		tmp = buff;
// 		read_err = read(fd, buff_read, BUFFER_SIZE);
// 		buff_read[BUFFER_SIZE] = '\0';
// 		if (read_err < 0)
// 			return (NULL);
// 		if(ft_strchr_m(buff_read, '\n') || read_err < BUFFER_SIZE)
// 		{
// 			if (ft_strchr_m(buff_read, '\n'))
// 				buff = newline_join(buff, buff_read, cursor);
// 			else if (read_err < BUFFER_SIZE)
// 			{
// 				buff = ft_strjoin(buff, buff_read);
// 				free(tmp);
// 			}
// 			return(buff);
// 		}
// 		buff = ft_strjoin(buff, buff_read);
// 		free(tmp);
// 	}
// }
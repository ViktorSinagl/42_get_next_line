
#include	"get_next_line.h"

char	*newline_join(char *buff, char *buff_read, char **cursor)
{
		size_t		n;
		size_t		i;
		char			*left;
		char			*tmp;

		tmp = *cursor;
		n = ft_strchr_m(buff_read, '\n');
		left = (char *)malloc((n + 2) * sizeof(char));
		i = 0;
		while (*buff_read != '\n')
		{
			left[i++] = *buff_read;
			buff_read++;
		}
		left[i] = '\n';
		left[++i] = '\0';	
		if (*buff == '\0')
			buff = left;	
		else
			buff = ft_strjoin(buff,left);
		*cursor = ft_strdup(++buff_read);
		if (tmp != NULL)
			free(tmp);
		return (buff);
}

char	*read_newline(int fd, char *buff, char **cursor, char *buff_read)
{
	ssize_t		read_err;
	char		*tmp;

	while(1)
	{
		tmp = buff;
		read_err = read(fd, buff_read, BUFFER_SIZE);
		buff_read[BUFFER_SIZE] = '\0';
		if (read_err < 0)
			return (NULL);
		if(ft_strchr_m(buff_read, '\n') || read_err < BUFFER_SIZE)
		{
			if (ft_strchr_m(buff_read, '\n'))
				buff = newline_join(buff, buff_read, cursor);
			else if (read_err < BUFFER_SIZE)
				buff = ft_strjoin(buff, buff_read);
			free(tmp);
			return(buff);
		}
		buff = ft_strjoin(buff, buff_read);
		free(tmp);
	}
}



char *get_next_line(int fd)
{
	static char	*cursor;
	char		*buff;
	char		*buff_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (cursor == NULL)
		buff = ft_strdup("");
	else
		buff = cursor;
	buff_read = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	memset(buff_read, '\0', BUFFER_SIZE + 1);
	if (buff_read == NULL)
		return(NULL);
	if (ft_strchr_m(buff, '\n'))
		buff = newline_join("",buff, &cursor);
	else
		buff = read_newline(fd, buff, &cursor, buff_read);
	free(buff_read);
	if (buff == NULL)
		return (NULL);
	return (buff);
}
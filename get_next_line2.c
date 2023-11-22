#include "get_next_line.h"

//external function: ft_strjoin
//external function: ft_strchr_m
//external function: ft_strdup
//external fuctnion: ft_strlen

char	*splitline(char *cursor, char **line)
{
	size_t	len;
		
	len = ft_strchr_m(cursor,'\n');
	*line = ft_substr(cursor, 0, len);
	cursor = ft_substr(cursor, len, ft_strlen(cursor));
	return (cursor);
}
char	*read_line(int fd, char *buff, char *cursor)
{
	int	read_err;
	char	*tmp;

	read_err = 1;
	while (read_err > 0)
	{
		read_err = read(fd, buff, BUFFER_SIZE);
		if (buff == NULL)
			return(NULL);
		if (buff == 0)
			break;
		tmp = cursor;
		cursor = ft_strjoin(cursor, buff);
		if (tmp != NULL)
			free(tmp);
		if (ft_strchr_m(cursor, '\n'))
			break;
	}
	return (cursor);
}

char	*get_next_line(int fd)
{
	static char	*cursor;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (cursor == NULL)
		cursor = ft_strdup("");
	buff = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	cursor = read_line(fd, buff, cursor);
	free(buff);
	if (line == NULL)
		return(NULL);
	cursor = splitline(fd, &line);
	return (line);
}
/* test jak menit hodnoty pointeru ktery je poslan do funkce jako parametr
void	function_test(char **line)
{
	*line = ft_strdup("ahoj jak se mas");
}

int main(){
	char *line;

	function_test(&line);
	printf("%s\n",line);
	return(0);
}
*/
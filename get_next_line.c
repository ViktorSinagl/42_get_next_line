#include "get_next_line.h"

//external function: ft_strjoin
//external function: ft_strchr_m
//external function: ft_strdup
//external fuctnion: ft_strlen

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*splitline(char **line, char *cursor)
{
	size_t	len;
	char		*tmp;
		
	tmp = cursor;
	len = ft_strchr_m(cursor,'\n');
	*line = ft_substr(cursor, 0, len);
	cursor = ft_substr(cursor, len, ft_strlen(cursor) + 1);
	if (tmp != NULL)
		free(tmp);
	return (cursor);

}
char	*read_line(int fd, char *buff, char *cursor)
{
	int	read_err;
	char	*tmp;

	while (1)
	{
		read_err = read(fd, buff, BUFFER_SIZE);
		if (read_err < 0)
			return(NULL);
		if (read_err == 0)
			break;
		buff[read_err] = '\0';
		if (cursor == NULL)
			cursor = ft_strdup("");
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
	buff = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	cursor = read_line(fd, buff, cursor);
	free(buff);
	if (cursor == NULL)
		return (NULL);
	if (*cursor == 0)
		return(NULL);
	if (!ft_strchr_m(cursor, '\n'))
	{
		line = cursor;
		cursor = NULL;
		return(line);
	}
	cursor = splitline(&line, cursor);
	return (line);
}

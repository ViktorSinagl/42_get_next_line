#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

//global variables
int BUFFER_SIZE = 2000;
char *BUFF_TST[20];

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strchr_m(const char *s, int c)
{
	char	*res;
	size_t	i;

	res = (char *)s;
	if (c > 127)
		return (0);
	i = 0;
	while (res[i] != '\0')
	{
		if (res[i] == c)
			return (i);
		i++;
	}
	if (res[i] == c)
		return (i);
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	unsigned char		*p_src;
	size_t				i;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	if (src < dest)
	{
		while (n--)
			p_dest[n] = p_src[n];
	}
	else
	{
		while (n--)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*sdup;
	size_t	n;

	n = 0;
	sdup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (sdup == NULL)
		return (NULL);
	while (s[n] != '\0')
	{
		sdup[n] = s[n];
		n++;
	}
	sdup[n] = '\0';
	return (sdup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		ft_memmove(str, s1, ft_strlen(s1) + 1);
		ft_memmove((str + ft_strlen(s1)), s2, ft_strlen(s2) + 1);
		return (str);
	}
	return (0);
}



char	*newline_join(char *buff, char *buff_read, char **cursor)
{
		size_t		n;
		size_t		i;
		char			*left;
		char			*tmp;

		tmp = *cursor;
		n = ft_strchr_m(buff_read, '\n');
		left = (char *)malloc((n + 1) * sizeof(char));
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
		buff_read[BUFFER_SIZE + 1] = '\0';
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

int main(void)
{
	int fd = open("readtext",O_RDONLY);
	char *a = get_next_line(fd);
	printf("%s",a)	;	
	free(a);
	// char *b = get_next_line(fd);
	// printf("%s",b)	;	
	// b = get_next_line(fd);
	// printf("%s",b)	;	
	// free(b);
	free(cursor);
	close(fd);
	return (0);
}

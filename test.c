#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <stdio.h>

//global variables
int BUFFER_SIZE = 10;
char *BUFF_TST[20];

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)s;
	if (c > 125)
		return (res);
	while (res[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (res[i] == c)
			return (res + i);
		i--;
	}
	return (NULL);
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
	return (NULL);
}

//NEW_LINE JOIN FUNCTION HERE

ssize_t	read_newline(int fd, char *buff)
{
	ssize_t		read_err;
	char		*buff_read;

	buff_read = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	if (buff_read == NULL)
		return (NULL);
	while (ft_strchr(buff_read, '\n') == NULL)
	{
		read_err = read(fd, buff_read, BUFFER_SIZE);
		if (read_err < 0)
		{
			free(buff);
			return (-1);
		}
		if (read_err < BUFFER_SIZE)
		{
			ft_strjoin(buff, buff_read);
			return(1);
		}
		ft_strjoin(buff, buff_read);
	}
	newline_join(buff, buff_read);
	return(2);
}



char *get_next_line(int fd)
{
	static char	*buff;
	ssize_t		err;
		
	if (fd < 0)
		return (NULL);
	//condition for checking if BUFFER_SIZE is bigger than max int number ? BUFFER_SIZE from subject declares as INT
	err = read_newline(fd, buff);
	if (err < 0)
		return (NULL);
	return (ft_strdup(buff));
}

int main(void)
{
	int fd = open("txt",O_RDONLY);
	char *a = get_next_line(fd);
	printf("%s\n",a)	;
	return (0);
}
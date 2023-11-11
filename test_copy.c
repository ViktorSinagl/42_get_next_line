#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
//global variables
int BUFFER_SIZE = 5;
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
		return (res);
	i = 0;
	while (res[i] != '\0')
	{
		if (res[i] == c)
			return (res);
		i++;
	}
	if (res[i] == c)
		return (i);
	return (NULL);
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



char	*newline_join(char *buff, char *buff_read, char ***cursor)
{
		size_t		n;
		size_t		i;
		char		*tmp;

		n = ft_strchar_m(buff_read);
		buff = (char *)malloc((n + 1) * sizeof(char));
		while (buff_read != '\n')
			buff[i++] = buff_read++;
		buff[i] = '\n';
		buff[i++] = '0';	
		if (**cursor != NULL)
			free(cursor);
		**cursor = (char *)malloc((ft_strlen(buff_read) - n + 1) * sizeof(char))
		i = 0;
		while (++buff_read != '\0')
			**cursor[i++] = buff_read;
		**cursor[i] = '0';
		return (buff);
}

char	*newline_join(char *buff, char *buff_read, char ***cursor)
{
	size_t		i;
	size_t 		j;
	char		*str_left;
	char		*tmp;	


	i = 0;
	while (buff_read[i] != '\n')
		i++;
	str_left = (char *)malloc(sizeof(char) * (i + 2));
	// printf("the strlen: %zu\n",ft_strlen(buff_read));
	// printf("the i: %zu\n",i);
	// printf("the malloc size of cursor: %zu\n", ft_strlen(buff_read) - 1 - i);
	//cursor = (char **)malloc(sizeof(char) * (ft_strlen(buff_read) - i -1));
	i = 0;
	while(buff_read[i] != '\n')
	{
		str_left[i] = buff_read[i];
		i++;
	}
	str_left[i] = '\n';
	str_left[i++] = '\0';
	tmp = buff;
	buff = ft_strjoin(buff, str_left);
	free(tmp);
	j = 0;
	**cursor = ft_strdup("ja");
	// while(buff_read[i] != '\0')
	// {
	// 	cursor[j] = buff_read[i];
	// 	j++; 
	// 	i++;
	// }
	//*cursor[j] = '\0';
	return (buff);
}

//NEW_LINE JOIN FUNCTION HERE

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
				buff = newline_join(buff, buff_read, &cursor);
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
	ssize_t		err;

	if (fd < 0)
		return (NULL);
	if (cursor == NULL)
		buff = ft_strdup("");
	else
		buff = cursor;
	buff_read = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	if (buff_read == NULL)
		return(NULL);
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
	printf("%s\n",a)	;	
	free(a);
	char *b = get_next_line(fd);
	printf("%s\n",b)	;	
	free(b);
	return (0);
}

//main pro cvicny test memory leak, pri prehravvani hodnoty buffer (tam kam se ukladaji buffer_read stringy, je treba prubezne uvolnovat pres pomocny pointer, jinak nam v pameti zustava misto)
// int		main(void)
// {
// 	char *tst;
// 	char *tst2;
// 	char *tst3;
// 	char *tmp;

// 	//testing freeing null pointer
// 	tst = NULL;
// 	tmp = tst;
// 	if (tmp != NULL)
// 		printf("memory allocated\n");

// 	//first init
// 	tst = ft_strdup("ahoj");


// 	//loop 1
// 	tmp = tst;
// 	tst2 = ft_strdup(" jak se mas\n");
// 	tst = ft_strjoin(tst,tst2);	
// 	free(tmp);

// 	//loop 2
// 	tmp = tst;
// 	tst3 = ft_strdup("--jde to\n");
// 	tst = ft_strjoin(tst, tst3);
// 	free(tmp);

// 	printf("%s",tst);
// 	free(tst), free(tst2), free(tst3); 
// }
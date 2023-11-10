#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include  <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
//global variables
int BUFFER_SIZE = 5;
char *BUFF_TST[20];


char	*newline_join(char *buff, char *buff_read, char *cursor)
{
	size_t		i;
	size_t 		j;
	char		*str_left;
	char		*tmp;	


	i = 0;
	while (buff_read[++i] != '\n')
	str_left = (char *)malloc(sizeof(char) * (i + 1));
	cursor = (char *)malloc(sizeof(char) * (ft_strlen(buff_read) - i -1));
	i = 0;
	while(buff_read[i] != '\0')
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
	while(buff_read[i] != '\0')
	{
		cursor[j] = buff_read[i];
		j++; 
		i++;
	}
	cursor[j] = '\0';
	return (buff);
}

//NEW_LINE JOIN FUNCTION HERE

ssize_t	read_newline(int fd, char *buff, char *cursor)
{
	ssize_t		read_err;
	char		*buff_read;
	char		*tmp;

	buff_read = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	if (buff_read == NULL)
		return(-2);
	while (ft_strchr(buff_read, '\n') == NULL)
	{
		//reading and adding null terminated character
		tmp = buff;
		read_err = read(fd, buff_read, BUFFER_SIZE);
		buff_read[BUFFER_SIZE + 1] = '\0';
		if (read_err < 0)
		{
			free(buff_read);
			return (-1);
		}
		buff = ft_strjoin(buff, buff_read);	
		if (tmp != NULL)
			free(tmp);
		if (read_err < BUFFER_SIZE)
		{
			free(buff_read);
			return(1);
		}
	}
	newline_join(buff, buff_read, cursor);
	free(buff_read);
	return(2);
}



char *get_next_line(int fd)
{
	static char	*cursor;
	char		*buff;
	ssize_t		err;

	if (fd < 0)
		return (NULL);
	buff = NULL;
	//condition for checking if BUFFER_SIZE is bigger than max int number ? BUFFER_SIZE from subject declares as INT
	err = read_newline(fd, buff, cursor);
	if (err < 0)
	{
		free(buff);
		return (NULL);
	}
	return (ft_strdup(buff));
}

int main(void)
{
	int fd = open("readtext",O_RDONLY);
	char *a = get_next_line(fd);
	printf("%s\n",a)	;
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
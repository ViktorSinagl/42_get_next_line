#vsinagl makefile for get_next_line project

SRCS:= get_next_line.c\
		get_next_line_utils.c
		
TSRCS:= get_next_line_utils.c\
		test.c

OBJS:= $(SRCS:.c=.o);

TOBJS:= $(TSRCS:.c=.o);

FLAGS = -Wall -Wextra -Werror

TARGET:= test

$(TARGET):	$(TOBJS)
	cc $(FLAGS) -c $(TSRCS)
	cc $(TOBJS) -o $(TARGET)
#vsinagl makefile for get_next_line project

SRCS:= get_next_line.c\
		get_next_line_utils.c
		
TSRCS:= 	get_next_line.c\
		get_next_line_utils.c\
		test.c

OBJS:= $(SRCS:.c=.o);
TOBJS:= $(TSRCS:.c=.o);

FLAGS = -Wall -Wextra -Werror
COMPILER = gcc

TARGET:= test

$(TARGET): $(SRCS)
	$(COMPILER) $(FLAGS) $(SRCS) $(TARGET).c get_next_line.h -o $(TARGET)

fclean:
	rm $(TARGET)

all: $(TARGET)

re: clean fclean all

.PHONY: clean fclean all re testclean testre





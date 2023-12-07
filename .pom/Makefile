#vsinagl makefile for get_next_line project

SRCS:= get_next_line.c\
		get_next_line_utils.c

SRCS_B:= get_next_line_bonus.c\
		get_next_line_utils_bonus.c
		
TSRCS:= 	get_next_line.c\
		get_next_line_utils.c

OBJS:= $(SRCS:.c=.o);
TOBJS:= $(TSRCS:.c=.o);

FLAGS = -Wall -Wextra -Werror
COMPILER = cc

TARGET:= test

BONUS:= bonus

$(TARGET): $(SRCS)
	$(COMPILER) $(FLAGS) -D BUFFER_SIZE=10 -g $(SRCS) test.c -o $(TARGET)

$(BONUS): 
	$(COMPILER) $(FLAGS) -D BUFFER_SIZE=10 -g $(SRCS_B) test_bonus.c -o $(BONUS)

fclean:
	rm $(TARGET)

all: $(TARGET)

re: clean fclean all

.PHONY: clean fclean all re testclean





CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = tree_utils.c utils.c vbc.c error_parser.c
NAME = vbc

OBJS = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)
clean: 
	rm -f *.o
fclean: clean
	rm -f vbc
re: fclean all

.PHONY: all clean fclean re

NAME = MCParis

CC = gcc

SRC = main.c find.c recup.c find_list.c

OBJS = $(SRC:.c=.o)

INC = projet.h

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -I /includes -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

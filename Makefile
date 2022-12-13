NAME = philo
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
LIBRARIES = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(LIBRARIES)

clean:
				$(RM) $(OBJS)

fclean: clean
				$(RM) $(NAME)

re: fclean all

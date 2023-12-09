# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 19:43:40 by moturki           #+#    #+#              #
#    Updated: 2023/12/09 19:44:27 by moturki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
SRCS = philosophers.c main.c ft_utils.c ft_init.c routine.c
OBJS = $(SRCS:.c=.o)
LIBRARIES = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARIES)

clean:
				$(RM) $(OBJS)

fclean: clean
				$(RM) $(NAME)

re: fclean all

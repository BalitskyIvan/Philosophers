# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmallado <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 19:35:08 by lmallado          #+#    #+#              #
#    Updated: 2020/12/04 19:35:11 by lmallado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo_one

HEADER = philo.h

SRCS = main.c \
		initializer.c \
		utils.c \
		detach.c \
		ft_itoa.c

O_FILE = $(patsubst %.c,%.o,$(SRCS))
D_FILE = $(patsubst %.c,%.d,$(SRCS))


FLAGS =# -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(O_FILE)
	gcc $(FLAGS) $(O_FILE) -o $(NAME) -lpthread

%.o: %.c philo.h
	gcc -c $(FLAGS) -I$(HEADER) -c $< -o $@ -MD

clean:
	rm -f $(O_FILE)
	rm -f $(D_FILE)

fclean: clean
	rm -f $(NAME)

re:		fclean all

include $(wildcards $(D_FILE))

.PHONY : all clean fclean re
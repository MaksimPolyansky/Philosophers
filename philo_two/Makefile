NAME		=	philo_two

HEADER		=	./includes/philo_two.h

CC			=	gcc

FLAGS		=	-Werror -Wall -Wextra -pthread

SRCS		=	./sources/philo_two.c \
				./sources/died.c \
				./sources/parse.c \
				./sources/utils.c \
				./sources/errors.c \
				./sources/inits.c

OBJS		=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

re	:fclean all

norm:
	norminette $(SRCS) $(HEADER)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm $(NAME)

de:
	gcc -g -pthread $(SRCS)

.PHONY: all clean fclean re

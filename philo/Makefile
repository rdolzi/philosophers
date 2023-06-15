NAME = push_swap
LIBFT = libft

SRCS = ./philo/main.c \
	./philo/philo_initialize.c ./philo/philo_routine.c \

FLAGS = -Wextra -Werror -Wall

CC = @gcc ${FLAGS}
RM = @rm -f

OBJS = ${SRCS:.c=.o}


$(NAME): $(OBJS) 
	@make -C $(LIBFT)
	$(CC) $(OBJS) main.c -o $(NAME)

all: $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	@make -C $(LIBFT)
	$(CC) Libft/libft.a $(OBJS) $(OBJS_BONUS) -o checker


clean:
	${RM} ${OBJS} $(OBJS_BONUS)
	@make clean -C $(LIBFT)

fclean: clean
	@make fclean -C $(LIBFT)
	${RM} ${NAME} checker
	
re: fclean all

.PHONY: all clean fclean re bonus
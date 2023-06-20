NAME = philo_bonus

SRCS = main.c \
	   philo_initialize.c \
	   philo_routine.c \

FLAGS = -Wextra -Werror -Wall
CC = @gcc ${FLAGS}
RM = @rm -f

OBJS = ${SRCS:.c=.o}

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
	
re: fclean all

.PHONY: all clean fclean re
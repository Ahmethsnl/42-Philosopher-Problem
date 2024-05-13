NAME	=	philo
SRC		=	philo.c start_action.c utils.c continue_utils.c
OBJS 	= 	$(SRC:.c=.o)
CC 		= 	@gcc
CFLAGS 	= 	-Wall -Wextra -Werror
RM	 	= 	rm -rf

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "The philosopher's problem is solving"
	@echo "------------------------------------"
	@echo "Executable philo ready to work"

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@echo "Object files deleted"

fclean:	clean
	@$(RM) $(NAME)
	@echo "-------------------------"
	@echo "Executable files deleted"

re:	fclean all

.PHONY: clean fclean re
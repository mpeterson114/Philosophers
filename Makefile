ORANGE =		\033[38;5;209m
CYAN =			\033[0;96m
PURPLE=			\033[0;35m
YELLOW =		\033[0;93m
RED =			\033[0;91m
GREEN =			\033[0;92m
WHITE =			\033[0;37m

NAME =	philo
SRC =	main.c \
		utils.c \
		init.c \
		threads.c \
		monitor.c \
		routine_actions.c \

SANITIZE = -g3 -fsanitize=thread
#SANITIZE = -g3 -fsanitize=address
#SANITIZE = -g3

CC = gcc
CFLAGS = -Wall -Werror -Wextra $(SANITIZE)
#-pthread -Ofast -O3 -march=native
REMOVE = rm -f 

%.o: %.c 
		@echo "$(YELLOW) Compiling	$(WHITE)$<"
		@$(CC) $(CFLAGS) -c $< -o $@

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
		@echo "\n$(GREEN)Objects and executables created successfully ✅\n"

clean:
		@$(REMOVE) $(OBJS)
		@echo "\n$(PURPLE) Objects cleaned successfully ✅\n"

fclean: 
		@$(REMOVE) $(OBJS)
		@$(REMOVE) $(NAME)
		@echo "\n$(ORANGE) Objects and executables deleted successfully ✅\n"

re:		fclean all

.PHONY: all clean fclean re

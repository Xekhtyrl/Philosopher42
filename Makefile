NAME = philo

INCLUDES = ./Includes

MY_SOURCES =	Src/parsing.c			\
				Src/routine.c			\
				Src/thread.c			\
				Src/clear_functions.c	\
				Src/utils.c				\
				main.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_END=\033[0m

CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g3

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@gcc $(CFLAGS) -o $(NAME) $(MY_OBJECTS)
	@echo "$(C_GREEN)$(NAME) compiled$(C_END)"

%.o:	%.c
	@gcc ${CFLAGS} -I $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(MY_OBJECTS) $(MY_OBJ_BONUS)
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

.PHONY: all clean fclean re
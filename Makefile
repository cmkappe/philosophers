
NAME	=	philo
HEADER	=	philosophers.h

SRC_DIR	=	src
OBJ_DIR =	src_o
UTILS_DIR =	utils

SRC_FILES		=	main.c init.c threads.c monitor_routine.c philo_routine.c helpers.c

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -O2 -g -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

NAME = minishell

CC = cc
C_FLAGS = -Wall -Wextra -Werror

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

LIBFT_PATH = ./Libft/
LIBFT = ./includes/$(LIBFT_PATH)libft.a

SRC = main.c\
	utils/utils.c\
	utils/utils1.c\
	builtin/builtin_commands.c\
	builtin/builtin_exit.c\
	parsing/parsing.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
INC = -I $(INC_PATH) -I $(LIBFT_PATH)

.PHONY: all clean fclean re

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)builtin
	mkdir -p $(OBJ_PATH)parsing
	mkdir -p $(OBJ_PATH)utils

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(C_FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -lreadline -lhistory

clean: 
	rm -rf $(OBJ_PATH)
	@echo "Object files removed"

fclean: clean
	rm -rf $(NAME)
	@echo "Objects and binary removed"

re: fclean all

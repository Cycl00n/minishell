NAME = minishell

CC = cc
C_FLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
OBJ_DIR = objs

LIBFT_DIR = Libft
LIBFT = includes/$(LIBFT_DIR)/libft.a

SRC = main.c\
	utils.c\

SOURCES = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INC = -I ./includes/

.PHONY: all clean fclean re

all: $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lhistory


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean: 
	rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	rm -rf $(NAME)
	@echo "Objects and binary removed"

re: fclean all

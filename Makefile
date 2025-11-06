NAME = minishell

CC = cc
C_FLAGS = -Wall -Wextra -Werror

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

LIBFT_PATH = ./Libft/
LIBFT = ./includes/$(LIBFT_PATH)libft.a

SRC = parsing/main_parsing.c\
parsing/ft_split_token.c\
utils/utils.c\
utils/utils1.c\

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(SRCS:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
INC = -I $(INC_PATH) -I $(LIBFT_PATH)

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)builtin
	mkdir -p $(OBJ_PATH)parsing
	mkdir -p $(OBJ_PATH)utils

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@ $(INC)


$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -lreadline -lhistory

$(LIBFT):
	make -C $(LIBFT_PATH)

clean: 
	rm -rf $(OBJ_PATH)
	@echo "Object files removed"

fclean: clean
	rm -rf $(NAME)
	@echo "Objects and binary removed"

re: fclean all

.PHONY: all clean fclean re

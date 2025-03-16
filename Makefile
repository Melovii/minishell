NAME			= 	minishell
CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror -Iincludes -I /home/my-home-dir/.local/include
LDFLAGS			= 	-L /home/my-home-dir/.local/lib -lreadline -lncurses
LIBFT			= 	libft/libft.a

SRC_DIR			= 	srcs
OBJ_DIR			= 	objs
UTILS_DIR		= 	$(SRC_DIR)/utils
BUILTINS_DIR	= 	$(SRC_DIR)/builtins
EXEC_DIR		= 	$(SRC_DIR)/exec
PARSER_DIR		= 	$(SRC_DIR)/parser
SIG_DIR			= 	$(SRC_DIR)/signals

SRCS			=	$(SRC_DIR)/main.c				\
					$(UTILS_DIR)/env_utils.c		\

OBJS			=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: default

default: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo Makefile run successfully!

# Ensure that subdirectories in objs exist before compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/utils
	@$(CC) $(CFLAGS) -c $< -o $@

# Create all necessary object directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/utils:
	@mkdir -p $(OBJ_DIR)/utils

$(LIBFT):
	@make -C libft bonus --silent

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft --silent

fclean: clean
	@rm -f $(NAME)

re: fclean all

leaks:
	@valgrind --leak-check=full		\
	--show-leak-kinds=all			\
	--track-origins=yes				\
	--verbose						\
	--log-file=valgrind-out.txt		\
	./minishell						\

test:
	bash tests.sh

.PHONY: all clean fclean re leaks test

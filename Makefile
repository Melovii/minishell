NAME			= 	minishell
CC				= 	cc
# CFLAGS			= 	-g -Iincludes -I /home/my-home-dir/.local/include
CFLAGS			= 	-Wall -Wextra -Werror -Iincludes -I /home/my-home-dir/.local/include
LDFLAGS			= 	-L /home/my-home-dir/.local/lib -lreadline -lncurses
LIBFT			= 	libft/libft.a

SRC_DIR			= 	srcs
OBJ_DIR			= 	objs

UTILS_DIR		= 	$(SRC_DIR)/utils
BUILTINS_DIR	= 	$(SRC_DIR)/builtins
EXEC_DIR		= 	$(SRC_DIR)/execution
PARSING_DIR		= 	$(SRC_DIR)/parsing
SIG_DIR			= 	$(SRC_DIR)/signals

SRCS			=	$(SRC_DIR)/main.c				\
					$(EXEC_DIR)/execute.c			\
					$(EXEC_DIR)/pipe.c				\
					$(PARSING_DIR)/tokenizer.c		\
					$(PARSING_DIR)/parser.c			\
					$(UTILS_DIR)/parsing_utils.c	\
					$(UTILS_DIR)/string_utils.c		\
					$(UTILS_DIR)/env_utils.c		\
					$(UTILS_DIR)/error_utils.c		\
					$(UTILS_DIR)/exec_utils.c		\
					# $(UTILS_DIR)/builtin_utils.c	\

OBJS			=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "Makefile run successfully!"

# Compile source files into object files inside objs/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Creates subdirectory for object file if it doesn't exist
	@$(CC) $(CFLAGS) -c $< -o $@

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

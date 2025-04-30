NAME			= 	minishell
CC				= 	cc
CFLAGS			= 	-g -Iincludes -I /home/my-home-dir/.local/include
# CFLAGS			= 	-Wall -Wextra -Werror -Iincludes -I /home/my-home-dir/.local/include
LDFLAGS			= 	-L /home/my-home-dir/.local/lib -lreadline -lncurses
LIBFT			= 	libft/libft.a

SRC_DIR			= 	srcs
OBJ_DIR			= 	objs

UTILS_DIR	= 	$(SRC_DIR)/utils
BUILTIN_DIR	= 	$(SRC_DIR)/builtins
ENV_DIR		= 	$(SRC_DIR)/env
EXEC_DIR	= 	$(SRC_DIR)/execution
PARSING_DIR	= 	$(SRC_DIR)/parsing
TOKENS_DIR	= 	$(PARSING_DIR)/tokenization
PARSE_DIR	= 	$(PARSING_DIR)/parse
EXP_DIR		= 	$(PARSING_DIR)/expansion


SRCS			=	$(SRC_DIR)/main.c				\
					$(SRC_DIR)/free.c				\
					$(SRC_DIR)/errors.c				\
					$(SRC_DIR)/signals.c			\
					$(TOKENS_DIR)/tokenizer.c		\
					$(TOKENS_DIR)/token_lst.c		\
					$(PARSE_DIR)/parser.c			\
					$(PARSE_DIR)/cmd_lst.c			\
					$(PARSE_DIR)/redirection.c		\
					$(PARSE_DIR)/env.c				\
					$(EXP_DIR)/expansion.c			\
					$(EXP_DIR)/expand_cmds.c		\
					$(EXP_DIR)/expansion_utils.c	\
					$(EXP_DIR)/measure_length.c		\
					$(EXEC_DIR)/execution.c			\
					$(EXEC_DIR)/exec_builtin.c		\
					$(EXEC_DIR)/child.c				\
					$(EXEC_DIR)/heredoc.c			\
					$(EXEC_DIR)/path.c				\
					$(EXEC_DIR)/pipe.c				\
					$(EXEC_DIR)/termios.c			\
					$(EXEC_DIR)/setup_redirection.c	\
					$(BUILTIN_DIR)/ft_cd.c			\
					$(BUILTIN_DIR)/ft_pwd.c			\
					$(BUILTIN_DIR)/ft_env.c			\
					$(BUILTIN_DIR)/ft_echo.c		\
					$(BUILTIN_DIR)/ft_exit.c		\
					$(BUILTIN_DIR)/ft_unset.c		\
					$(BUILTIN_DIR)/ft_export.c		\
					$(UTILS_DIR)/env_utils.c		\
					$(UTILS_DIR)/token_utils.c		\
					$(UTILS_DIR)/export_utils.c		\
					$(UTILS_DIR)/string_utils.c		\
					$(UTILS_DIR)/path_utils.c		\
					$(UTILS_DIR)/syntax_utils.c		\
					$(UTILS_DIR)/quote_utils.c		\
					$(UTILS_DIR)/unquote_utils.c	\




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

#* Program and compiler settings
NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iincludes -Ilib/readline/include
LDFLAGS		=	-Llib/readline/lib -Wl,-rpath=$(PWD)/lib/readline/lib -lreadline -lncurses
LIBFT		=	libft/libft.a

#* Readline settings
READLINE_VERSION	=	8.2
READLINE_DIR		=	lib/readline
READLINE_TARBALL	=	readline-$(READLINE_VERSION).tar.gz
READLINE_SRC_DIR	=	readline-$(READLINE_VERSION)
READLINE_A			=	readline_build

#* Directories
SRC_DIR		=	srcs
OBJ_DIR		=	objs
SUPP_DIR	=	supps
UTILS_DIR	=	$(SRC_DIR)/utils
BUILTIN_DIR	=	$(SRC_DIR)/builtins
ENV_DIR		=	$(SRC_DIR)/env
EXEC_DIR	=	$(SRC_DIR)/execution
PARSING_DIR	=	$(SRC_DIR)/parsing
TOKENS_DIR	=	$(PARSING_DIR)/tokenization
PARSE_DIR	=	$(PARSING_DIR)/parse
EXP_DIR		=	$(PARSING_DIR)/expansion

#* Colors
YELLOW	=	\033[1;33m
GREEN	=	\033[1;32m
BLUE	=	\033[1;34m
RED		=	\033[1;31m
CYAN	=	\033[1;36m
RESET	=	\033[0m
BOLD	=	\033[1m

#* Source files
SRCS		=	$(SRC_DIR)/main.c					\
				$(SRC_DIR)/free.c					\
				$(SRC_DIR)/errors.c					\
				$(SRC_DIR)/signals.c				\
				$(TOKENS_DIR)/tokenizer.c			\
				$(TOKENS_DIR)/token_lst.c			\
				$(PARSE_DIR)/env.c					\
				$(PARSE_DIR)/parser.c				\
				$(PARSE_DIR)/cmd_lst.c				\
				$(PARSE_DIR)/redirection.c			\
				$(PARSE_DIR)/redirection_utils.c	\
				$(PARSE_DIR)/setup_redirection.c	\
				$(EXP_DIR)/fill.c					\
				$(EXP_DIR)/expansion.c				\
				$(EXP_DIR)/expand_cmds.c			\
				$(EXP_DIR)/measure_length.c			\
				$(EXP_DIR)/expansion_utils.c		\
				$(EXEC_DIR)/pipe.c					\
				$(EXEC_DIR)/path.c					\
				$(EXEC_DIR)/child.c					\
				$(EXEC_DIR)/termios.c				\
				$(EXEC_DIR)/heredoc.c				\
				$(EXEC_DIR)/execution.c				\
				$(EXEC_DIR)/pipe_utils.c			\
				$(EXEC_DIR)/exec_builtin.c			\
				$(BUILTIN_DIR)/ft_cd.c				\
				$(BUILTIN_DIR)/ft_pwd.c				\
				$(BUILTIN_DIR)/ft_env.c				\
				$(BUILTIN_DIR)/ft_echo.c			\
				$(BUILTIN_DIR)/ft_exit.c			\
				$(BUILTIN_DIR)/ft_unset.c			\
				$(BUILTIN_DIR)/ft_export.c			\
				$(BUILTIN_DIR)/ft_cd_utils.c		\
				$(BUILTIN_DIR)/ft_export_utils.c	\
				$(BUILTIN_DIR)/ft_export_utils2.c	\
				$(UTILS_DIR)/env_utils.c			\
				$(UTILS_DIR)/path_utils.c			\
				$(UTILS_DIR)/quote_utils.c			\
				$(UTILS_DIR)/token_utils.c			\
				$(UTILS_DIR)/string_utils.c			\
				$(UTILS_DIR)/syntax_utils.c			\
				$(UTILS_DIR)/unquote_utils.c		\

OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(READLINE_A) $(LIBFT) $(OBJS)
	@echo "$(CYAN)🔧 Linking objects and libraries...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Build complete! Executable created: $(NAME)$(RESET)"

#* Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)📦 Compiling: $(notdir $<)$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

#* Build libft
$(LIBFT):
	@echo "$(BLUE)📚 Building libft...$(RESET)"
	@make -C libft bonus --silent

#* Build readline
$(READLINE_A):
	@echo "$(BLUE)⬇️  Downloading and building readline...$(RESET)"

	@if [ ! -f $(READLINE_TARBALL) ]; then								\
		echo "$(CYAN)📥 Downloading readline...$(RESET)";				\
		curl -LO https://ftp.gnu.org/gnu/readline/$(READLINE_TARBALL);	\
	fi

	@echo "$(CYAN)📂 Extracting...$(RESET)"
	@rm -rf $(READLINE_SRC_DIR)
	@tar -xzf $(READLINE_TARBALL)

	@echo "$(CYAN)⚙️  Configuring...$(RESET)"
	@cd $(READLINE_SRC_DIR) && ./configure --prefix=$(PWD)/$(READLINE_DIR) --enable-shared --disable-static > /dev/null

	@echo "$(CYAN)🔨 Building...$(RESET)"
	@cd $(READLINE_SRC_DIR) && make > /dev/null

	@echo "$(CYAN)📦 Installing...$(RESET)"
	@cd $(READLINE_SRC_DIR) && make install > /dev/null

	@rm -rf $(READLINE_SRC_DIR)
	@echo "$(GREEN)✅ Readline build complete$(RESET)"
	@touch $(READLINE_A)

#* Clean readline
readline_uninstall:
	@echo "$(RED)🗑️  Uninstalling readline...$(RESET)"
	@rm -rf $(READLINE_DIR)
	@rm -f $(READLINE_TARBALL) $(READLINE_A)

#* Clean objects
clean: readline_uninstall
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf lib
	@make fclean -C libft --silent

fclean: clean
	@echo "$(RED)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

leaks:
	@echo "$(CYAN)🧠 Running valgrind...$(RESET)"
	@valgrind --leak-check=full						\
		--suppressions=$(SUPP_DIR)/readline.supp	\
		--show-leak-kinds=all 						\
		--track-origins=yes 						\
		--track-fds=yes 							\
		--verbose 									\
		./$(NAME)

test: all
	@cd minishell_tester && ./tester && cd -

count_lines:
	@echo "$(CYAN)📊 Counting uncommented C lines...$(RESET)"
	@grep -vE '^\s*//|^\s*/\*|^\s*\*/|^\s*\*' $(SRCS) | wc -l 		\
	| awk -v green="$(GREEN)" -v bold="$(BOLD)" -v reset="$(RESET)" \
	'{ printf "📄 %s%sUncommented lines:%s %s%d%s\n", bold, green, reset, green, $$1, reset }'

.PHONY: all readline_uninstall clean fclean re leaks test count_lines

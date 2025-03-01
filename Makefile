NAME		= minishell
CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -lreadline -Iincludes
CFLAGS		= -Iincludes -lreadline # ! temporarily ignoring errors while testing
# CFLAGS		= -g # ! for debugging
LIBFT		= libft/libft.a

SRC_DIR=srcs

SRCS =	$(SRC_DIR)/main.c		\
		$(SRC_DIR)/parse.c		\
		$(SRC_DIR)/pipe.c		\
		$(SRC_DIR)/signal.c		\
		$(SRC_DIR)/execute.c	\
		$(SRC_DIR)/commands.c	\

OBJS = $(SRCS:.c=.o)

all: default

default: $(NAME)

$(NAME): 	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS)				\
			$(LIBFT) -o $(NAME)
			@echo Makefile run successfully!

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		make -C libft

clean:
		@rm $(OBJS)
		@make fclean -C libft
	
fclean: clean
		@rm -fr $(NAME)

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

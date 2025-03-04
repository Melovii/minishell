# TODO: replace LIBFT

NAME		= minishell
CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -Iincludes -I /home/my-home-dir/.local/include
CFLAGS		= -Iincludes -I /home/my-home-dir/.local/include
LDFLAGS		= -L /home/my-home-dir/.local/lib -lreadline -lncurses
LIBFT		= libft/libft.a

SRC_DIR		= srcs
PARSE_DIR 	= srcs/parse

SRCS =	$(SRC_DIR)/main.c		\
		$(SRC_DIR)/signal.c		\
#		$(SRC_DIR)/parse.c		\
		$(SRC_DIR)/pipe.c		\
		$(SRC_DIR)/execute.c	\
		$(SRC_DIR)/commands.c	\

OBJS = $(SRCS:.c=.o)

all: default

default: $(NAME)

$(NAME): 	$(LIBFT) $(OBJS)
			@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
			@echo Makefile run successfully!

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		@make -C libft bonus --silent

clean:
		@rm -f $(OBJS)
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

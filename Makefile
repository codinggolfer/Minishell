NAME	=	minishell

CC		=	CC
CFLAGS	=	#-Wall -Wextra -Werror
RM		=	rm -f

HEADERS	=	-I ~/.brew/opt/readline/include

INCLUDES	=	-lreadline -L ~/.brew/opt/readline/lib

FILES	=	minishell.c \
			pipex.c \
			child.c \
			signal.c \
			array_utils.c \
			create_envp.c \
			lexer.c \
			list_utils.c \
			t_list_utils.c \
			token_utils.c \
			parser.c \
			str_utils.c \
			builtins.c \
			redirect.c 


LIBFT	=	libft/libft.a

#PIPEX	=	pipex/pipex.a

OBJECTS	=	$(FILES:.c=.o)

all:	minishell

$(NAME):	$(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(HEADERS) $(INCLUDES) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	$(RM) $(NAME) $(OBJECTS)

fclean: clean
	make fclean -C libft
	$(RM) $(OBJECTS)
	
re: fclean $(NAME)

.PHONY: all clean fclean re
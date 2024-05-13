NAME	=	minishell

CC		=	CC
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

HEADERS	=	-I ~/.brew/opt/readline/include

INCLUDES	=	-lreadline -L ~/.brew/opt/readline/lib

FILES	=	minishell.c \
			



LIBFT	=	libft/libft.a

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
	$(RM) $(NAME) $(OBJECTS)
	
re: fclean $(NAME)

.PHONY: all clean fclean re
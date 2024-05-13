NAME	=	minishell

CC		=	CC
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

FILES	=	



LIBFT	=	libft/libft.a

OBJECTS	=	$(FILES:.c=.o)

all:	minishell

$(NAME):	$(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 12:27:21 by hzibari           #+#    #+#              #
#    Updated: 2024/05/13 16:38:21 by eagbomei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT	=	../libft/libft.a

NAME	=	pipex

SRCS	=	pipex.c \
			child.c

OFILES	=	$(SRCS:.c=.o)

CC		=	cc
RM		=	-rm -f
CFLAGS	=	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(LIBFT) ${OFILES}
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft

%.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@

clean:
		make fclean -C libft
		$(RM) $(OFILES)
	
fclean: clean
		make fclean -C libft
		$(RM) $(NAME) $(OFILES)

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 12:27:21 by hzibari           #+#    #+#              #
#    Updated: 2024/05/13 16:06:28 by hzibari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT	=	libft/libft.a

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
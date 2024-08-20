NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g
RM		=	rm -f

HEADERS	=	-I ~/.brew/opt/readline/include

INCLUDES	=	-lreadline -L ~/.brew/opt/readline/lib

FILES	=	minishell.c \
			signal.c \
			Utils/array_utils.c \
			create_envp.c \
			lexer.c \
			Utils/list_utils.c \
			Utils/t_list_utils.c \
			Utils/token_utils.c \
			parser.c \
			Utils/str_utils.c \
			builtins/builtins.c \
			Redirects/redirect.c \
			Vars/var_utils.c \
			Vars/var_utils2.c \
			error_exit.c \
			builtins/builtin_export.c \
			builtins/builtin_unset.c \
			builtins/builtin_exit.c \
			builtins/builtin_cd.c \
			cmds/cmd_exe_helper.c \
			cmds/cmd_paths.c \
			cmds/cmd_path_helper.c \
			cmds/cmd_exe.c \
			cmds/cmd_exe_multi.c \
			Redirects/redirect_utils.c \
			Redirects/redirect_handler.c \
			Builtins/export_env.c \


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
	$(RM) $(OBJECTS)

fclean: clean
	make fclean -C libft
	$(RM) $(OBJECTS) $(NAME)
	
re: fclean $(NAME)

.PHONY: all clean fclean re
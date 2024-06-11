/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:59:55 by eagbomei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/11 13:53:37 by eagbomei         ###   ########.fr       */
=======
/*   Updated: 2024/06/10 16:17:35 by hzibari          ###   ########.fr       */
>>>>>>> fdfc809d6990e4c0e163a08a312991e8ffea1202
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <term.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_cmd
{
	char	**cmd;
}	t_cmd;

typedef struct s_list
{
	char			*env;
	struct s_list	*next;
	int				in_fd;
	int				out_fd;
	t_cmd			cmd;
}	t_list;

//pipex struct
typedef struct s_pipe
{
	int		fd[2];
	char	**env;
	char	**path;
	int		flag;
}	t_pipe;

typedef struct s_input
{
	char	**own_env;
	char	*line;
	char	**tokens;
	t_list	*vars;
}	t_input;

// env
t_list	*set_env(char **env);

//init functions:
void	rebuild_envp(t_input *data);
t_list	*create_list(t_list *head, char *env);
t_list	*new_list(char *env);
int		listsize(t_list *head);
t_list	*listlast(t_list *head);

//utils
char	**realloc_and_add(char **src, char *str);
void	free_2darray(char **array);
int		count_arg_array(char **array);

//readline functions:
int		handle_line(t_input *data);
int		check_closed(t_input *data);

//signals:
void	newliner(int signal);

//lexer / parsing
int		lexer(t_input *data);
int		is_token(char c);
int		bunny_ears(char *line, int start, int bunny_ears);
int		parser(t_input *data);

// pipex funtions

int		pipex_main(int ac, char **av, char **env);
void	pipex(int fd1, int fd2, char **av, t_pipe *struk);
void	ft_error(char *msg);
void	child_one(int fd1, char *av, t_pipe *struk);
void	child_two(int fd2, char *av, t_pipe *struk);
char	*get_command(char **path, char *arg);
void	put_msg(char *av);
char	*find_path(char **env);

#endif

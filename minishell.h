/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:59:55 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 14:10:10 by eagbomei         ###   ########.fr       */
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

typedef struct s_env
{
	char	*env_str;
}	t_env;

typedef struct s_list
{
	t_env			*env;
	char			*token;
	char			*cmds;
	char			*array;
	struct s_list	*next;
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

//readline functions:
int		handle_line(t_input *data);

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

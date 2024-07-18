/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:59:55 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/18 14:22:55 by eagbomei         ###   ########.fr       */
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
# include <errno.h>

typedef struct s_cmd
{
	char	**cmd;
}	t_cmd;

typedef struct s_list
{
	char			*env;
	int				in_fd;
	int				out_fd;
	t_cmd			cmd;
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
	int		stdin_backup;
	int		stdout_backup;
	char	**own_env;
	char	*line;
	char	**tokens;
	char	*cwd;
	int		exit_code;
	t_list	*vars;
	t_list	*cmds;
}	t_input;

// env
t_list	*set_env(char **env);

//init functions:
void	rebuild_envp(t_input *data);
t_list	*create_list(t_list *head, char *env);
t_list	*new_list_env(char *env);
int		listsize(t_list *head);
t_list	*listlast(t_list *head);
t_list	*new_list_cmd(char **cmd);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);

//utils
char	**realloc_and_add(char **src, char *str);
void	free_2darray(char **array);
int		count_arg_array(char **array);
int		ft_strcmp(char *s1, char *s2);
int		strcmp_equal(char *s1, char *s2);

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
char	*append_line(char *line, char *ret);

// pipex funtions

int		pipex_main(int ac, char **av, char **env);
void	pipex(int fd1, int fd2, char **av, t_pipe *struk);
void	ft_error(char *msg);
void	child_one(int fd1, char *av, t_pipe *struk);
void	child_two(int fd2, char *av, t_pipe *struk);
char	*get_command(char **path, char *arg);
void	put_msg(char *av);
char	*find_path(char **env);

// builtins
int 	handle_builtins(char *cmd, char **arg, t_input *data);
int 	ft_strcmp(char *s1, char *s2);
int		cd_error(void);
int 	builtin_cd(char **arg, t_input *data);

// vars

int		find_symbol(char *line, int found);
int		get_keywords(char *line, int stop);
char 	*access_var(t_input *data, char *var);
void	dollar_sign(t_input *data);
t_list  *find_var(t_list *vars, char *find);

// redirect
int		check_redirect_errors(t_input *data);
int		is_redirect(char *arg);
int 	count_args_skip_redirections(char **args);
int		redirection_type(char *arg);
int		has_redirect(char **arg);
int		is_redirect(char *arg);


//error
int		error_msg(char *cmd, char *context, char *msg, int code);

#endif

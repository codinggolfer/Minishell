/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:59:55 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/17 15:01:40 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include "pipex.h"
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
	t_env 	*env;
	struct s_list	*next;
}	t_list;

typedef struct s_input
{
	char	**own_env;
	char	*line;
	char	**tokens;
	t_list	*vars;
}	t_input;

//init functions:
void	rebuild_envp(t_input *data);
t_list	*create_list(t_list *head, char *env);
t_list	*new_list(char *env);

//readline functions:
int		handle_line(t_input *data);

//signals:
void	newliner(int signal);

#endif
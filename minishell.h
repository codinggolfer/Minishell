/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:59:55 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/14 16:18:41 by eagbomei         ###   ########.fr       */
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
	
}	t_env;

typedef struct s_list
{
	struct s_list	*next;
}	t_list;
typedef struct s_input
{
	char	**env;
	t_list	*vars;
}	t_input;


void	rebuild_envp(t_input *data);

#endif
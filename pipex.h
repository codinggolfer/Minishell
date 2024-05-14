/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:15:09 by hzibari           #+#    #+#             */
/*   Updated: 2024/05/14 14:17:11 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipe
{
	int		fd[2];
	char	**env;
	char	**path;
	int		flag;

}	t_pipe;

int		pipex_main(int ac, char **av, char **env);
void	pipex(int fd1, int fd2, char **av, t_pipe *struk);
void	ft_error(char *msg);
void	child_one(int fd1, char *av, t_pipe *struk);
void	child_two(int fd2, char *av, t_pipe *struk);
char	*get_command(char **path, char *arg);
void	put_msg(char *av);
char	*find_path(char **env);

#endif

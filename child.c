/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:34:36 by hzibari           #+#    #+#             */
/*   Updated: 2024/05/22 13:41:19 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_msg(char *av)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit (127);
}

void	put_error_msg(char *av)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (127);
}

char	*get_command(char **path, char *arg)
{
	char	*temp;
	char	*cmd;

	if (!path)
		return (0);
	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		cmd = ft_strjoin(temp, arg);
		free(temp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		path++;
	}
	return (0);
}

void	child_one(int fd1, char *av, t_pipe *struk)
{
	char		**cmd_arg;
	char		*cmd;

	if (struk->flag == 1)
		exit(1);
	dup2(struk->fd[1], STDOUT_FILENO);
	close(struk->fd[0]);
	dup2(fd1, STDIN_FILENO);
	close(struk->fd[1]);
	close(fd1);
	cmd_arg = ft_split(av, ' ');
	if (access(cmd_arg[0], 0) == 0)
	{
		cmd = cmd_arg[0];
		if (execve(cmd, cmd_arg, struk->env) < 0)
			exit (1);
	}
	else
		cmd = get_command(struk->path, cmd_arg[0]);
	if (ft_strchr(av, '/'))
		put_msg(av);
	else if (!cmd)
		put_error_msg(av);
	if (execve(cmd, cmd_arg, struk->env) < 0)
		exit(1);
}

void	child_two(int fd2, char *av, t_pipe *struk)
{
	char		**cmd_arg;
	char		*cmd;

	dup2(struk->fd[0], STDIN_FILENO);
	close(struk->fd[1]);
	dup2(fd2, STDOUT_FILENO);
	close (struk->fd[0]);
	close (fd2);
	cmd_arg = ft_split(av, ' ');
	if (access(cmd_arg[0], 0) == 0)
	{
		cmd = cmd_arg[0];
		if (execve(cmd, cmd_arg, struk->env) < 0)
			exit (1);
	}
	else
		cmd = get_command(struk->path, cmd_arg[0]);
	if (ft_strchr(av, '/'))
		put_msg(av);
	else if (!cmd)
		put_error_msg(av);
	if (execve(cmd, cmd_arg, struk->env) < 0)
		exit (1);
}

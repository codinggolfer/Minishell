/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:17:36 by hzibari           #+#    #+#             */
/*   Updated: 2024/05/22 13:41:09 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
	{
		env++;
		if (*env == NULL)
			return (0);
	}
	return (*env + 5);
}

void	pipex(int fd1, int fd2, char **av, t_pipe *struk)
{
	pid_t	child1;
	pid_t	child2;
	int		status;

	if (pipe(struk->fd) < 0)
		ft_error("pipe: ");
	child1 = fork();
	if (child1 < 0)
		ft_error("fork: ");
	if (child1 == 0)
		child_one(fd1, av[2], struk);
	child2 = fork();
	if (child2 < 0)
		ft_error("fork: ");
	if (child2 == 0)
		child_two(fd2, av[3], struk);
	close(fd1);
	close(fd2);
	close(struk->fd[1]);
	close(struk->fd[0]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	pipex_main(int ac, char **av, char **env)
{
	int				fd1;
	int				fd2;
	static t_pipe	struk;

	if (*env == NULL)
	{
		ft_putendl_fd("Error input", 1);
		return (0);
	}
	fd1 = open (av[1], O_RDONLY);
	fd2 = open (av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(av[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		struk.flag = 1;
	}
	struk.env = env;
	struk.path = ft_split(find_path(env), ':');
	pipex(fd1, fd2, av, &struk);
	return (0);
}

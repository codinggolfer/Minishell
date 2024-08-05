/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:41 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/05 20:03:16 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirect_input(char *filename, int *in_fd)
{
	int		fd;

	if (is_redirect(filename))
		return (-1);
	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
		return (error_msg(NULL, filename, "No such file or directory", 1));
	dup2(fd, *in_fd);
	return (0);
}

int	handle_all_redirect_output(char *filename, int *out_fd, int decider)
{
	int	fd;

	if (is_redirect(filename))
		return (-1);
	if (decider == 3)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (error_msg(NULL, filename, "File could not be opened", 1));
	dup2(fd, *out_fd);
	printf("here\n");
	close(fd);
	return (0);
}

int	heredoc_child(char *seperate, int *stor, int std_in)
{
	char	*line;

	line = NULL;
	close(stor[0]);
	dup2(std_in, STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		rl_redisplay();
		if (!line)
		{
			error_msg("warning", seperate,
				"here-document at line 28 delimited by end-of-file", 0);
			break ;
		}
		if (ft_strcmp(line, seperate) == 0)
			break ;
		write(stor[1], line, ft_strlen(line));
		write(stor[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	exit(420);
}

int	handle_redirect_input_heredoc(char *seperate, int *in_fd, int std_in)
{
	pid_t	child_fd;
	int		stor[2];

	if (is_redirect(seperate))
		return (-1);
	pipe(stor);
	child_fd = fork();
	if (!child_fd)
		heredoc_child(seperate, stor, std_in);
	close(stor[1]);
	waitpid(child_fd, 0, 0);
	dup2(stor[0], *in_fd);
	return (0);
}
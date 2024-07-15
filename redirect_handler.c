/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:41 by halgordziba       #+#    #+#             */
/*   Updated: 2024/07/15 16:15:20 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_input(char *filename, int *in_fd)
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

int	handle_all_redir_output(char *filename, int *out_fd)
{
	int	fd;

	if (is_redirect(filename))
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (error_msg(NULL, filename, "File could not be opened", 1));
	dup2(fd, *out_fd);
	close(fd);
	return (0);
}

int	handle_redir_input_heredoc(char *delimiter, int *in_fd, int std_in)
{
	int		child_fd;
	int		storage[2];

	if (is_redirect(delimiter))
		return (-1);
	pipe(storage);
	child_fd = fork();
	if (!child_fd)
		heredoc_child(delimiter, storage, std_in);
	close(storage[1]);
	waitpid(child_fd, 0, 0);
	dup2(storage[0], *in_fd);
	return (0);
}
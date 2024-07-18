/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:01:19 by halgordziba       #+#    #+#             */
/*   Updated: 2024/07/18 14:21:06 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ENOENT: If the file does not exist.
//ENOTDIR: If the component of the path is not a directory.

int	error_msg(char *cmd, char *context, char *msg, int code)
{
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (context)
	{
		write(STDERR_FILENO, context, ft_strlen(context));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (code);
}
int	cd_error(void)
{
	if (errno == ENOENT)
		error_msg("cd", NULL, "No such file or directory", 1);
	else if (errno == ENOTDIR)
		error_msg("cd", NULL, "Not a directory", 1);
	return (1);
}
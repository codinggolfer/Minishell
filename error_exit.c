/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:01:19 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/05 18:23:10 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *cmd, char *context, char *msg, int code)
{
	if (cmd)
	{
		write(1, "babatunde shell: ", 18);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (context)
	{
		write(1, "babatunde shell: ", 18);
		write(STDERR_FILENO, context, ft_strlen(context));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (code);
}
void	cleaner(t_input *data)
{
	dup2(data->stdin_backup, STDIN_FILENO);
	dup2(data->stdout_backup, STDOUT_FILENO);
	if (data->cmds)
		free_list(data->cmds);
	if (data->line)
		free(data->line);
}

int	get_error(char *msg)
{
	if (errno == ENOENT)
		error_msg("cd", msg, "No such file or directory", 1);
	else if (errno == ENOTDIR)
		error_msg("cd", msg, "Not a directory", 1);
	return (1);
}
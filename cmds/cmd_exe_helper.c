/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:03:52 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/02 16:18:24 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_execute(char *path, char **arg, char **my_env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(path, arg, my_env) == -1)
		exit(errno);
}

int	parent_execute(t_input *data, pid_t pid)
{
	int	stat;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &stat, 0);
	return (get_exit_code(data, stat));
}

int	get_cmd_counter(t_input *data)
{
	t_list	*count;
	int		ret;

	ret = 0;
	count = data->cmds;
	while (count)
	{
		++ret;
		count = count->next;
	}
	return (ret);
}
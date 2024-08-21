/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:03:52 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/21 20:27:55 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_execute(char *path, char **arg, char **my_env)
{
	check_signal(1);
	// close(3);
	// close(4);
	// close(0);
	// close(1);
	if (execve(path, arg, my_env) == -1)
		exit(errno);
	exit(127);
}

int	parent_execute(t_input *data, pid_t pid)
{
	int	stat;

	//close(1);
	//close(2);
	//close(0);
	check_signal(0);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:30:09 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/19 20:58:32 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_all_cmds(int count, pid_t last_child, t_input *data)
{
	int	status;

	status = 0;
	while (count)
	{
		waitpid(last_child, &status, 0);
		if (last_child)
			get_exit_code(data, status);
		last_child = 0;
		--count;
	}
}

static void	clean_pipes(int send, int count, int *pipe_stor)
{
	if (send)
		close(pipe_stor[2]);
	if (send != count - 1)
	{
		close(pipe_stor[1]);
		pipe_stor[2] = pipe_stor[0];
	}
}

static void	in_child(int last, t_input *data, t_list *current, int *toclose)
{
	close(data->stdout_backup);
	close(data->stdin_backup);
	check_signal(1);
	if (!last){
		close(toclose[0]);
	}
	//close(toclose[1]);
	close(toclose[2]);
	if (handle_redirections(current->cmd.cmd, current,
			data->stdin_backup) == -1)
		exit (1);
	current->cmd.cmd = cmds_no_redirect(current->cmd.cmd);
	dup2(current->in_fd, STDIN_FILENO);
	dup2(current->out_fd, STDOUT_FILENO);
	exit (single_cmd(data, current));
}

static void	fix_fd(int sent, int cmd_count, int *pipe_stor, t_list *current)
{
	if (sent != cmd_count - 1)
	{
		pipe(pipe_stor);
		current->out_fd = pipe_stor[1];
		//close (pipe_stor[1]);
	}
	if (sent)
		current->in_fd = pipe_stor[2];
}

void	multi_commands(t_input *data)
{
	t_list	*currentent;
	int		cmd_count;
	int		send;
	int		pipe_stor[3];
	pid_t	last_child;

	cmd_count = get_cmd_counter(data);
	currentent = data->cmds;
	send = 0;
	while (send < cmd_count)
	{
		fix_fd(send, cmd_count, &pipe_stor[0], currentent);
		last_child = fork();
		if (last_child == 0)
			in_child((send == cmd_count - 1), data, currentent, &pipe_stor[0]);
		else
		{
			clean_pipes(send, cmd_count, &pipe_stor[0]);
			++send;
			currentent = currentent->next;
		}
		waitpid(last_child, NULL, 0);
	}
	check_signal(1);
	wait_all_cmds(cmd_count, last_child, data);
}

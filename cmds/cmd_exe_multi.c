/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:30:09 by halgordziba       #+#    #+#             */
/*   Updated: 2024/07/30 17:38:28 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_all_commands(int cmd_count, int last_child_pid, t_input *data)
{
	int	status;

	while (cmd_count)
	{
		waitpid(last_child_pid, &status, 0);
		if (last_child_pid)
			get_exit_code(data, status);
		last_child_pid = 0;
		--cmd_count;
	}
}

static void	clean_pipes(int dispatched, int cmd_count,
		int *pipe_storage)
{
	if (dispatched)
		close(pipe_storage[2]);
	if (dispatched != cmd_count - 1)
	{
		close(pipe_storage[1]);
		pipe_storage[2] = pipe_storage[0];
	}
}

static void	in_child(int last_var, t_input *data, t_list *curr, int to_close)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!(last_var))
		close(to_close);
	if (is_redirect(data->cmds->cmd.cmd[0]))
		if (handle_redirections(curr->cmd.cmd, curr, data->stdin_backup) == -1)
			exit (1);
	if (is_redirect(data->cmds->cmd.cmd[0]))
		curr->cmd.cmd = cmds_no_redirect(curr->cmd.cmd);
	dup2(curr->in_fd, STDIN_FILENO);
	dup2(curr->out_fd, STDOUT_FILENO);
	exit (single_cmd(data, curr));
}

static void	fix_fd(int sent, int cmd_count, int *pipe_stor, t_list *current)
{
	if (sent != cmd_count - 1)
	{
		pipe(pipe_stor);
		current->out_fd = pipe_stor[1];
	}
	if (sent)
		current->in_fd = pipe_stor[2];
}

void	multi_commands(t_input *data)
{
    t_list  *current;
    int     cmd_count;
    int     send;
    int     pipe_stor[3];
    pid_t   last_child;

    cmd_count = get_command_count(data);
    current = data->cmds;
    send = 0;
    while(send < cmd_count)
    {
		fix_fd(send, cmd_count, &pipe_stor[0], current);
		last_child = fork();
		if (last_child == 0)
			in_child((send == cmd_count - 1), data, current, pipe_stor[0]);
		else
		{
			clean_pipes(send, cmd_count, &pipe_stor[0]);
			++send;
			current = current->next;
		}
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_all_commands(cmd_count, last_child, data);
}
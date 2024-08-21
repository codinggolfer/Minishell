/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:41:04 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/21 18:29:31 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void first_child(t_input *data, t_list *current, int toclose)
{
	//close(data->stdout_backup);
	//close(data->stdin_backup);
	check_signal(1);
	// if (!last){}
	// close(toclose);
	if (handle_redirections(current->cmd.cmd, current,
			data->stdin_backup) == -1)
		exit (1);
	current->cmd.cmd = cmds_no_redirect(current->cmd.cmd);
	dup2(toclose, STDOUT_FILENO);
	close(toclose);
	dup2(current->in_fd, STDIN_FILENO);
	close(current->in_fd);
	exit (single_cmd(data, current));
}

static void	middle_child(t_input *data, t_list *current)
{
	//close(data->stdout_backup);
	//close(data->stdin_backup);
	check_signal(1);
	// if (!last){}
	// close(toclose);
	if (handle_redirections(current->cmd.cmd, current,
			data->stdin_backup) == -1)
		exit (1);
	current->cmd.cmd = cmds_no_redirect(current->cmd.cmd);
	dup2(current->in_fd, STDIN_FILENO);
	close(current->in_fd);
	dup2(current->out_fd, STDOUT_FILENO);
	close(current->out_fd);
	exit (single_cmd(data, current));
}

static void last_child(t_input *data, t_list *current, int toclose)
{
	//close(data->stdout_backup);
	//close(data->stdin_backup);
	check_signal(1);
	// if (!last){}
	// close(toclose);
	if (handle_redirections(current->cmd.cmd, current,
			data->stdin_backup) == -1)
		exit (1);
	current->cmd.cmd = cmds_no_redirect(current->cmd.cmd);
	dup2(toclose, STDIN_FILENO);
	close(toclose);
	dup2(current->out_fd, STDOUT_FILENO);
	close(current->out_fd);
	exit (single_cmd(data, current));
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

void multi_cmd_loop(int send, int cmd_count, t_input *data, t_list *current)
{
	pid_t	child;
	int		pipe_stor[3];
	
	while (send < cmd_count)
	{
		fix_fd(send, cmd_count, &pipe_stor[0], current);
		child = fork();
		if (child == 0)
		{
			if (send == 0)
				first_child(data, current, pipe_stor[1]);
			else if (send > 0 && send < cmd_count -1)
				middle_child(data, current);
			else if (send == cmd_count - 1)
				last_child(data, current, pipe_stor[0]);
		}
		else
		{
			clean_pipes(send, cmd_count, &pipe_stor[0]);
			++send;
			current = current->next;
		}
		waitpid(child, NULL, 0);
	}
	check_signal(1);
	wait_all_cmds(cmd_count, child, data);
}

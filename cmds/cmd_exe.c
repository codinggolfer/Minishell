/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:04:50 by halgordziba       #+#    #+#             */
/*   Updated: 2024/07/23 15:05:59 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int single_cmd(t_input *data, t_list *cmds)
{
    int     exit_stat;
    char    *cmd;
    char    **cmd_path;

    cmd = ft_strdup(cmds->cmd.cmd[0]);
    exit_stat = handle_builtins(cmd, cmds->cmd.cmd, data);
    if (exit_stat == -1)
    {
		cmd_path = get_cmd_path(data, cmd);
		exit_stat = execute_cmd(data, cmd_path, cmds->cmd.cmd, cmd);
		if (cmd_path)
			free_2darray(&cmd_path);
    }
    else
        if (cmd)
            free(cmd);
    return (exit_stat);
}

int	check_pipes(t_input *data)
{
	t_list	*cur;

	cur = data->cmds;
	while (cur)
	{
		if (!cur->cmd.cmd)
		{
			data->exit_code = error_msg("minishell", NULL,
					"syntax error near unexpected token", 2);
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

void run_cmd(t_input *data)
{
    int exit_status;

    exit_status = 0;
    if (data->cmds->next)
    {
		if (check_pipes(data))
			multi_commands(data);  //need to be made
    }
    else
    {
        if(!data->cmds->cmd.cmd)
            return ;
		exit_status = handle_redirections(data->cmds->cmd.cmd,
				data->cmds, data->stdin_backup);
		if (exit_status == 1)
		{
			data->exit_code = exit_status;
			return ;
		}
		data->cmds->cmd.cmd = cmds_no_redirect(data->cmds->cmd.cmd);
		data->exit_code = single_command(data, data->cmds);
	}
}

int execute_cmd(t_input *data, char **cmd_paths, char **args, char *cmd)
{
	int i;
	pid_t child;

	i = 0;
	rebuild_envp(data);
	if (!cmd_paths)
		return (error_msg(NULL, cmd, "No such file or directory", 127));
	while(cmd_paths[i])
	{
		if (args[0])
			free(args[0]);
		args[0] = ft_strdup(cmd_paths[i]);
		if (!(access(args[0], X_OK)))
		{
			child = fork();
			if (!child)
				child_execute(cmd_paths[i], args, data->own_env);
			else
				return (parent_execute(data, child));
		}
		i++;
	}
	return (error_msg(NULL, cmd, "No such file or directory", 127));
}
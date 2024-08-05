/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:04:50 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/02 16:20:31 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int single_cmd(t_input *data, t_list *cmds)
{
    int     exit_code;
    char    *cmd;
    char    **path;

    cmd = ft_strdup(cmds->cmd.cmd[0]);
    exit_code = handle_builtins(cmd, cmds->cmd.cmd, data);
    if (exit_code == -1)
    {
		path = get_cmd_path(data, cmd);
		exit_code = execute_cmd(data, path, cmds->cmd.cmd, cmd);
		if (path)
			free_2darray(path);
    }
    else
	{
        if (cmd)
            free(cmd);
	}
    return (exit_code);
}

int	get_exit_code(t_input *data, int exit_code)
{
	if(WIFEXITED(exit_code))
		data->exit_code = WEXITSTATUS(exit_code);
	else
	{
		if(WIFSIGNALED(exit_code))
			data->exit_code = 130;
	}
	return (data->exit_code);
}

int	check_pipes(t_input *data)
{
	t_list	*current;

	current = data->cmds;
	while (current)
	{
		if (!current->cmd.cmd)
		{
			data->exit_code = error_msg("minishell", NULL,
					"syntax error near unexpected token", 2);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

void	run_cmd(t_input *data)
{
    int exit_code;

    exit_code = 0;
    if (data->cmds->next)
    {
		if (check_pipes(data))
			multi_commands(data);
    }
    else
    {
        if(!data->cmds->cmd.cmd)
            return ;
		exit_code = handle_redirections(data->cmds->cmd.cmd,
				data->cmds, data->stdin_backup);
		if (exit_code == 1)
		{
			data->exit_code = exit_code;
			return ;
		}
		data->cmds->cmd.cmd = cmds_no_redirect(data->cmds->cmd.cmd);
		data->exit_code = single_cmd(data, data->cmds);
	}
}

int execute_cmd(t_input *data, char **paths, char **args, char *cmd)
{
	int i;
	pid_t child;

	i = 0;
	rebuild_envp(data);
	if (!paths)
		return (error_msg(NULL, cmd, "No such file or directory", 127));
	while(paths[i] && cmd)
	{
		if (args[0])
			free(args[0]);
		args[0] = ft_strdup(paths[i]);
		if (!(access(args[0], X_OK)))
		{
			child = fork();
			if (!child)
				child_execute(paths[i], args, data->own_env);
			else
				return (parent_execute(data, child));
		}
		i++;
	}
	return (error_msg(NULL, cmd, "command not found", 127));
}
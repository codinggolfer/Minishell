/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:04:50 by halgordziba       #+#    #+#             */
/*   Updated: 2024/07/15 15:13:23 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_pipes(t_input *data)
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
		if (check_valid_pipes(data))
			multiple_commands(data);  //need to be made
    }
    else
    {
        if(!data->cmds->cmd.cmd)
            return ;
		exit_status = handle_redirect(data->cmds->cmd.cmd,
				data->cmds, data->stdin_backup);
		if (exit_status == 1)
		{
			data->exit_code = exit_status;
			return ;
		}
		data->cmds->cmd.cmd = get_cmd_args_without_redirect
			(data->cmds->cmd.cmd);
		data->exit_code = single_command(data, data->cmds);
	}
}
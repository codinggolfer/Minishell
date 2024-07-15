/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:23:02 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/15 15:11:17 by halgordziba      ###   ########.fr       */
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
        
    }
    else
        if (cmd)
            free(cmd);
    return (exit_stat);
}

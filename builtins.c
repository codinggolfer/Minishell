/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:02:01 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/16 15:28:23 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(char **arg)
{
    int i;
    int new_line;
    
    i = 1;
    new_line = 1;
    if (ft_strcmp("echo -n", arg[0]))
        new_line = 0;
    while (arg[i])
    {
        write(1, arg[i], ft_strlen(arg[i]));
        i++;
        if (arg[i] != NULL)
            write(1, " ", 1);
    }
    if (new_line)
        write (1, "\n", 1);
    return (0);
    
}
int builtin_pwd(t_input *data)
{
    printf("%s\n", data->cwd);
    return (0);
}

int builtin_env(char **own_env)
{
    int i;

    i = 0;
    while (own_env[i])
    {
        printf("%s\n", own_env[i]);
        i++;
    }
    return (0);
}

int handle_builtins(char *cmd, char **arg, t_input *data)
{
    if (ft_strcmp(cmd,"echo") == 0)
       return (builtin_echo(arg));
    else if (ft_strcmp(cmd,"pwd") == 0)
        return (builtin_pwd(data));
    else if (ft_strcmp(cmd, "env") == 0)
       return (builtin_env(data->own_env));
    // else if (ft_strcmp(cmd, "cd") == 0)
    //     builtin_cd(arg, data); //TODO
    // else if (ft_strcmp(cmd, "export"))
    //     builtin_export(arg, data); //TODO
    // else if (ft_strcmp(cmd, "unset"))
    //     builtin_unset(arg, data); //TODO
    // else if (ft_strcmp(cmd, "exit"))
    //     builtin_exit(arg); //TODO
    else    
        return (-1);
}
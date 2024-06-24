/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:02:01 by eagbomei          #+#    #+#             */
/*   Updated: 2024/06/24 14:39:04 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_echo(char **arg)
{
    int i;
    int new_line;
    
    i = 1;
    if (ft_strcmp("echo -n", arg[0]))
    {
        new_line = 0;
    }
    while (arg[i])
    {
        printf("%s", arg[i]);
        i++;
    }
    if (new_line)
        write (1, "\n", 1);
    return (0);
    
}

int handle_builtins(char *cmd, char **arg, t_input *data)
{
    if (ft_strcmp("echo", cmd) == 0)
        builtin_echo(arg);
    return (0);
}
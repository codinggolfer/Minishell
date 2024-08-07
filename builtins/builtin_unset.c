/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:18 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/05 14:35:56 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_unset(char **arg, t_input *data)
{
    int     i;
    t_list  *list;
    t_list  *del;

    i = 1;
    list = data->vars;
    while (arg[i])
    {
        if (!ft_strcmp(arg[i], "_"))
        {
            i++;
            continue ;
        }
        del = find_var(list, arg[i]);
        if (del)
        {
            remove_env(&data->vars, del);
            rebuild_envp(data);
        }
        i++;
    }
    return (0);
}
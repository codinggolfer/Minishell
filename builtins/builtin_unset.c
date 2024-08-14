/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:18 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/14 16:18:46 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_unset(char **arg, t_input *data)
{
    int     i;
    t_list  *list;
    t_list  *del;

    i = 0;
    list = data->vars;
    while (arg[++i])
    {
        if (!ft_strcmp(arg[i], ""))
            continue ;
        del = find_var(list, arg[i]);
        if (del)
        {
            if (list == del)
            {
                list = del->next;
                free(del->env);
                del->env = ft_strdup("");
            }
            else
                remove_env(&data->vars, del);
            rebuild_envp(data);
        }
    }
    return (0);
}
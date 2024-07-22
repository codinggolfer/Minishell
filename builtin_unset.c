/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:18 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/22 14:50:28 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            remove_env(&data->vars, del);
        i++;
    }
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:28:43 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/24 15:43:05 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_export(t_list *node)
{
    int i;
    int get_pos;

    i = 0;
    get_pos = get_position(node);
    write(1, "declare -x ", 11);
    if (get_pos != -1)
    {
        while (i <= get_pos)
            write(1, node->env[i++], 1);
        write(1, "\"", 1);
        while (node->env[i] != '\0')
            write(1, node->env[i++], 1);
        write(1, "\"\n", 2);
    }
    else 
    {
        write(1, node->env, ft_strlen(node->env));
        write(1, "\n", 1);
    }
}

int builtin_export(char **arg, t_input *data)
{
    int len;

    len = count_arg_array(data->own_env);
}
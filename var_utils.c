/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:59:49 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/01 15:49:48 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int break_down(char *ret, int *index, char **str)
{
    index[2] = 
}

void    innit_rd_vars(int *spec, int *index, char **str)
{
    *spec = 0;
    index[0] = 0;
    index[1] = 0;
    index[2] = 0;
    str[4] = NULL;
}

void dollar_sign(t_input *data)
{
    int     special;
    int     index[3];
    char    *ret;
    char    *str[5];

    innit_rd_vars(&special, index, str);
    ret = ft_strdup(data->line);
    while (find_symbol(&ret[index[1]], '$') != -1)
    {
        if (ret[index[1]] == '\"')
            special = !special;
        else if (ret[index[1]] == '\'' && !special)
            index[1] = bunny_ears(ret, index[1], '\'');
        else if (ret[index[1]] == '$')
        {
            if (break_down(ret, index, str))
                handle_special()
        }
        
    }
}
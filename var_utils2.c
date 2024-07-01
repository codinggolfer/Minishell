/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:50:46 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/01 18:24:26 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_keywords(char *line, int stop)
{
    stop++;
    while (line[stop] && line[stop] != ' ' && !is_token(line[stop]) && line[stop] != '$')
        stop++;
    return (stop--);
}

char *access_var(t_input *data, char *var)
{
    t_list *temp;

    temp = data->vars;
    if (!var)
        return ("");
    if (var[0] == '?')
        return (ft_itoa(data->exit_code));
    while (temp)
    {
        if (strcmp_equal(temp->env, var) == 0)
            
    }
}
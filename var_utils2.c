/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:50:46 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/16 15:08:02 by eagbomei         ###   ########.fr       */
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

int get_position(t_list *node)
{
    int i;

    i = 0;
    while (node->env[i] != '\0')
    {
        if (node->env[i] == '=')
            return (i);
        i++;
    }
    return (-1);
}

char    *get_val(t_list *node)
{
    int     pos;
    int     i;
    char    *val;

    pos = 0;
    i = 0;
    if (get_position(node) == -1)
        return (ft_strdup(""));
    pos = get_position(node) + 1;
    val = ft_calloc(ft_strlen(node->env) - pos +1, sizeof(char));
    while (node->env[pos])
    {
        val[i] = node->env[pos];
        i++;
        pos++;
    }
    return (val);
}


char *access_var(t_input *data, char *var)
{
    t_list *temp;

    temp = data->vars;
    if (!var)
        return ("");
    if (var[0] == '?')
        return (ft_itoa(data->exit_code));
    while (temp != NULL)
    {
        if (strcmp_equal(temp->env, var) == 0)
            return (get_val(temp));
        temp = temp->next;
    }
    return (ft_strdup(""));
}

t_list  *find_var(t_list *vars, char *find)
{
    t_list *node;

    node = vars;
    while (node)
    {
        if (!strcmp_equal(node->env, find))
            get_val(node);
        node = node->next;
    }
    return (NULL);
}
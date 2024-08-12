/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:28:43 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/12 17:18:01 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
            write(1, &node->env[i++], 1);
        write(1, "\"", 1);
        while (node->env[i] != '\0')
            write(1, &node->env[i++], 1);
        write(1, "\"\n", 2);
    }
    else 
    {
        write(1, node->env, ft_strlen(node->env));
        write(1, "\n", 1);
    }
}

char    *var_name(char *str)
{
    int i;
    int j;
    char *ret;
    
    i = 0;
    j = 0;
    while (str[i] != '\0' && str[i] != '=')
        i++;
    ret = malloc (sizeof(char) * i + 1);
    while (j < i)
    {
        ret[j] = str[j];
        j++;
    }
    ret[j] = '\0';
    return (ret);
}

int pre_print_vars(t_list *list)
{
    int     list_size;
    t_list  *curr_node;
    t_list  *smallest_node;

    list_size = listsize(list);
    //reset_printed(list);
    curr_node = list;
    while (list_size-- > 0)
    {
        // while (curr_node)
        // {
        //     if (curr_node->env[0] < smallest_node->env[0])
        smallest_node = curr_node;
        display_export(smallest_node);
        curr_node = curr_node->next;
        // }
    }
    return (0);
}

void    replace_var(char *str, t_list *node)
{
    if (find_symbol(str, '=') == -1)
        return ;
    free (node->env);
    node->env = ft_strdup(str);
}

int builtin_export(char **arg, t_input *data)
{
    int     i;
    t_list  *node;
    char    *new_var_name;

    i = 0;
    if (arg[1] == NULL)
        return (pre_print_vars(data->vars));
    while (arg[++i] != NULL)
    {
        if (ft_isascii(arg[i][0]) && !ft_isalpha(arg[i][0]) && arg[i][0] != '_')
        {
            if (is_redirect(arg[i]))
                return (0);
            return (error_msg("export", arg[i], "not a valid identifier", 1));
        }
        new_var_name = var_name(arg[i]);
        node = find_var(data->vars, new_var_name);
        free (new_var_name);
        if (node == NULL)
            ft_lstadd_back(&data->vars, new_list_env(ft_strdup(arg[i])));
        else
            replace_var(arg[i], node);
    }
    rebuild_envp(data);
    return (0);
}
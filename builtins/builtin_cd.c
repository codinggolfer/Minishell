/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:27:31 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/05 16:35:41 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_cd_path(int size, char **arg, t_input *data)
{
    char    *path;

    path = NULL;
    if (size == 1 || arg[1][0] == '~')
    {
        path = access_var(data, "HOME");
        if (ft_strlen(path) == 0)
        {
            error_msg("cd", NULL, "HOME not set", 1);
            return (NULL);
        }
    }
    else if (arg[1][0] == '-')
    {
        path = access_var(data, "OLDPWD");
        if (ft_strlen(path) == 0)
        {
            error_msg("cd", NULL, "OLDPWD not set", 1);
            return (NULL);
        }
        printf("%s\n", path);
    }
    else
        path = ft_strdup(arg[1]);
    return (path);
}
void    update_env_cd(t_input **data)
{
    t_list  *node;

    node = find_var((*data)->vars, "OLDPWD");
    if (node == NULL)
    {
        node = new_list_env(ft_strjoin(ft_strdup("OLDPWD="), (*data)->cwd));
        ft_lstadd_back(&(*data)->vars, node);
    }
    else
        node->env = ft_strjoin(ft_strdup("OLDPWD="), (*data)->cwd);
    free((*data)->cwd);
    (*data)->cwd = getcwd(NULL, 1024);
    node = find_var((*data)->vars, "PWD");
    if (node == NULL)
    {
        node = new_list_env(ft_strjoin(ft_strdup("PWD="), (*data)->cwd));
        ft_lstadd_back(&(*data)->vars, node);
    }
    else
        node->env = ft_strjoin(ft_strdup("PWD="), (*data)->cwd); 
}

int builtin_cd(char **arg, t_input *data)
{
    int     i;
    char    *path;

    i = count_arg_array(arg);
    path = NULL;
    if (i > 2)
        return (error_msg("cd", NULL, "too many arguments", 1));
    path = get_cd_path(i, arg, data);
    if (!path)
        return (1);
    if (chdir(path) == -1)
       return (get_error(path));
    update_env_cd(&data);
    return (0);
}
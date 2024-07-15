/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:43:04 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/15 16:25:10 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *next_redirect(char **arg, int index)
{
    int *redirect;

    if (index >= count_arg_array(arg))
        return (NULL);
    while (arg[index])
    {
        redirect[0] = redirection_type(arg[index]);
        if (redirect[0] != 0)
        {
            redirect[1] = index;
            return (redirect);
        }
        index++;
    }
    redirect[0] = -1;
    redirect[1] = -1;
    return (redirect);
}

char **cmds_no_redirect(char **arg)
{
    int     i;
    int     j;
    int     old_len;
    int     len;
    char    **ret;

    old_len = count_arg_array(arg);
    len = count_args_skip_redirections(arg);
    i = 0;
    j = 0;
    ret = malloc (sizeof(char *) * len + 1);
    while (i < old_len)
    {
        if (is_redirect(arg[i]))
            i += 2;
        else
            ret[j++] = ft_strdup(arg[i++]);
    }
    ret[len] = NULL;
    free_2darray(arg);
    return (ret);
    
}

int switchdirect(int *info, t_list *lst, char *arg, int stdin)
{
/*NEEEDS THE FUNCTIONS FROM HELPERS TO SEND THEM*/
    
    if (info[0] == 1)
        return ();
    else if (info[0] == 2)
        return ();
    else if (info[0] == 3)
        return ();
    else if (info[0] == 4)
        return ();
    else
        return (1);
}

int handle_redirections(char **arg, t_list *list, int std_in)
{
    int i;
    int *redirect_info;

    i = 0;
    if (!has_redirect(arg))
        return (0);
    while (arg[i])
    {
        redirect_info = next_redirect(arg, i);
        if (redirect_info == NULL)
            return (-1);
        if (redirect_info[0] == -1 && redirect_info[1] == -1)
            break ;
        i = redirect_info[1] + 1;
        if (switchdirect(redirect_info, list, arg[i], std_in) == 1)
        {
            free (redirect_info);
            return (1);
        }
    }
    if (redirect_info)
        free (redirect_info);
    return (0);
}
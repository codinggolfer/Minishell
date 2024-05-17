/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:56:39 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/17 15:07:44 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_node(t_list *node)
{
    if (node->env->env_str != NULL)
        free (node->env->env_str);
}
void    free_list(t_list *lst)
{
    t_list  *temp;
    
    temp = lst;
    while (!lst)
    {
        temp = lst->next;
        free (lst);
        lst = temp;
    }
    lst = NULL;
}
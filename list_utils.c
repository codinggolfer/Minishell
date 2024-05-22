/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:56:39 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 13:20:35 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_list *node)
{
	if (node->env->env_str != NULL)
		free (node->env->env_str);
}

void	free_list(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (!lst)
	{
		temp = lst->next;
		free (lst);
		lst = temp;
	}
	lst = NULL;
}

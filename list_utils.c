/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:56:39 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 14:10:01 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_list *node)
{
	if (node->env->env_str != NULL)
		free (node->env->env_str);
}

int	listsize(t_list *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
t_list	*listlast(t_list *head)
{
	while (head)
	{
		if (head->next == NULL)
			return (head);
		head = head->next;
	}
	return (head);
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

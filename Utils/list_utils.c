/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:56:39 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 14:37:28 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_list *node)
{
	if (node->env != NULL)
		free (node->env);
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

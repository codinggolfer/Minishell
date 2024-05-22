/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:28 by eromonagbom       #+#    #+#             */
/*   Updated: 2024/05/22 14:44:23 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_list(char *env)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->env = ft_strdup(env);
	head->next = NULL;
	return (head);
}

t_list	*create_list(t_list *head, char *env)
{
	t_list	*new;
	t_list	*temp;

	new = new_list(env);
	if (!listsize(head))
		head = new;
	else
	{
		temp = listlast(head);
		temp->next = new;
	}
	return (head);
}

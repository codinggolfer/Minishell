/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:28 by eromonagbom       #+#    #+#             */
/*   Updated: 2024/06/26 14:51:52 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_list_env(char *env)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->env = ft_strdup(env);
	head->next = NULL;
	return (head);
}

t_list	*new_list_cmd(char **cmd)
{
	t_list	*list;

	list = (t_list *) malloc (sizeof(t_list));
	if (!list)
		return (NULL);
	list ->env = NULL;
	list ->cmd.cmd = ft_split(*cmd, ' ');
	list ->next = NULL;
	list->in_fd = STDIN_FILENO;
	list->out_fd = STDOUT_FILENO;
	return (list);
}

t_list	*create_list(t_list *head, char *env)
{
	t_list	*new;
	t_list	*temp;

	new = new_list_env(env);
	if (!listsize(head))
		head = new;
	else
	{
		temp = listlast(head);
		temp->next = new;
	}
	return (head);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if ((*lst) == NULL)
		*lst = new;
	else
		listlast(*lst)-> next = new;
}
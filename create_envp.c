/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:07:50 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/22 16:39:35 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rebuild_envp(t_input *data)
{
	int		i;
	t_list	*node;
	t_list	*list;

	i = 0;
	node = data->vars;
	list = node;
	if (data->own_env != NULL)
		free(data->own_env);
	data->own_env = calloc (sizeof(char *), listsize(list) + 1);
	if (!data->own_env)
	{
		data->own_env = NULL;
		return ;
	}
	while (list != NULL)
	{
		if (ft_strchr(list->env, '='))
		{
			data->own_env[i] = list->env;
			i++;
		}
		list = list->next;
	}
	data->own_env[i] = NULL;
}

t_list	*set_env(char **env)
{
	int		i;
	t_list	*node;

	i = 0;
	node = NULL;
	while (env[i])
	{
		node = create_list(node, env[i]);
		if (!node)
			exit(1);
		i++;
	}
	return (node);
}

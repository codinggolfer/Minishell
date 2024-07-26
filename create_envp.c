/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:07:50 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 14:32:18 by hzibari          ###   ########.fr       */
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
	data->own_env = malloc (sizeof(char *) * listsize(list) + 1);
	if (!data->own_env)
		exit (1); // need to add better protections in the future
	while (list != NULL)
	{
		data->own_env[i] = ft_strdup(list->env);
		i++;
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

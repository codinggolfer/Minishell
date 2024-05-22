/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:07:50 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 13:20:42 by hzibari          ###   ########.fr       */
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
		ft_error("malloc failure"); // need to add better protections in the future
	while (list != NULL)
	{
		data->own_env[i] = ft_strdup(list->env->env_str);
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
			ft_error("node creation failure");
		i++;
	}
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:33:11 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/20 21:48:46 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	replace_var(char *str, t_list *node)
{
	if (find_symbol(str, '=') == -1)
		return ;
	free (node->env);
	node->env = ft_strdup(str);
}

void	check_to_add_env(t_input *data, t_list *node, char *arg)
{
	if (node == NULL)
		ft_lstadd_back(&data->vars, new_list_env(arg));
	else
		replace_var(arg, node);
	if (ft_strchr(arg, '='))
		rebuild_envp(data);
}

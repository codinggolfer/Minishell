/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:18 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/22 16:45:21 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **arg, t_input *data)
{
	int		i;
	t_list	*list;
	t_list	*del;

	i = 0;
	list = data->vars;
	while (arg[++i])
	{
		if (!ft_strcmp(arg[i], "_"))
			continue ;
		del = find_var(list, arg[i]);
		if (del)
		{
			if (list == del)
			{
				list = del->next;
				free(del->env);
				del->env = ft_strdup("");
			}
			else
				remove_env(&data->vars, del);
			rebuild_envp(data);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:15 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/01 17:58:57 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirect(char *arg)
{
	if (arg == 0)
		return (0);
	if (ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0
		|| ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0)
	{
		return (1);
	}
	return (0);
}

int	has_redirect(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (is_redirect(arg[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	redirection_type(char *arg)
{
	if (!is_redirect(arg))
		return (0);
	if (!ft_strcmp(arg, "<"))
		return (1);
	if (!ft_strcmp(arg, "<<"))
		return (2);
	if (!ft_strcmp(arg, ">"))
		return (3);
	if (!ft_strcmp(arg, ">>"))
		return (4);
	return (-1);
}
int count_args_skip_redirections(char **args)
{
	int	i;
	int	ret;
	int len;

	ret = 0;
	i = 0;
	len = count_arg_array(args);
	while (i < len)
	{
		if (is_redirect(args[i]))
			i += 2;
		else
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

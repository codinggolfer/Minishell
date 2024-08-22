/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:02:01 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/22 19:35:42 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(char **arg)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (arg[1] && !ft_strcmp(arg[1], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		i++;
		if (arg[i] != NULL)
			write(1, " ", 1);
	}
	if (new_line)
		write (1, "\n", 1);
	return (0);
}

int	builtin_pwd(t_input *data)
{
	printf("%s\n", data->cwd);
	return (0);
}

int	builtin_env(char **own_env)
{
	int	i;

	i = 0;
	while (own_env[i])
	{
		if (ft_strlen(own_env[i]) != 0)
			printf("%s\n", own_env[i]);
		i++;
	}
	return (0);
}

int	handle_builtins(char *cmd, char **arg, t_input *data)
{
	if (cmd == 0)
		return (0);
	if (ft_strcmp2(cmd, "echo") == 0)
		return (builtin_echo(arg));
	else if (ft_strcmp2(cmd, "pwd") == 0)
		return (builtin_pwd(data));
	else if (ft_strcmp2(cmd, "env") == 0)
		return (builtin_env(data->own_env));
	else if (ft_strcmp2(cmd, "cd") == 0)
		return (builtin_cd(arg, data));
	else if (ft_strcmp2(cmd, "export") == 0)
		return (builtin_export(arg, data));
	else if (ft_strcmp2(cmd, "unset") == 0)
		return (builtin_unset(arg, data));
	else if (ft_strcmp2(cmd, "exit") == 0)
		return (builtin_exit(data, arg));
	else
		return (-1);
}

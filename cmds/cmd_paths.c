/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:59:28 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/19 21:01:32 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_to_path(char **paths, char *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*to_append;

	i = 1;
	j = 0;
	len = ft_strlen(cmd);
	to_append = (char *) malloc (sizeof(char) * len + 2);
	to_append[0] = '/';
	while (j < len)
		to_append[i++] = cmd[j++];
	to_append[len + 1] = '\0';
	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (paths[i][len - 1] == '/')
			paths[i] = append_line(paths[i], cmd);
		else
			paths[i] = append_line(paths[i], to_append);
		i++;
	}
	free(to_append);
}

char	*get_path_env(t_input *data)
{
	t_list	*lst;
	char	*ret;

	lst = data->vars;
	while (lst != NULL)
	{
		if (strcmp_equal(lst->env, "PATH") == 0)
		{
			ret = lst->env;
			return (ret + 5);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	**get_cmd_path(t_input *data, char *cmd)
{
	char	*full_path;
	char	**cmd_paths;

	if (is_executable(cmd) || is_absolute(cmd))
	{
		cmd_paths = (char **) malloc(sizeof(char *) * 2);
		cmd_paths[0] = ft_strdup(cmd);
		cmd_paths[1] = NULL;
	}
	else
	{
		full_path = get_path_env(data);
		if (!full_path)
			return (NULL);
		cmd_paths = ft_split(full_path, ':');
		append_to_path(cmd_paths, cmd);
	}
	return (cmd_paths);
}

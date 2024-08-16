/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:07 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/05 19:28:27 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_next_pipe(char **tokens, int *find_cmd)
{
	if (tokens && !ft_strcmp(tokens[find_cmd[1]], "|"))
		find_cmd[1]++;
	if (tokens && ft_strcmp(tokens[find_cmd[1]], "|") == 1)
		find_cmd[1]++;
	find_cmd[0] = find_cmd[1];
	while (tokens[find_cmd[1]])
	{
		if (!ft_strcmp(tokens[find_cmd[1]], "|"))
			break ;
		find_cmd[1]++;
	}
}

int	remove_ears(char **tokens)
{
	int	ret_val;

	ret_val = ((*tokens)[0] == '\"' || (*tokens)[0] == '\'');
	if ((*tokens)[0] == '\"')
	{
		(*tokens) = ft_strtrim((*tokens), "\"");
	}
	else if ((*tokens)[0] == '\'')
		(*tokens) = ft_strtrim((*tokens), "\'");
	return (ret_val);
}

void	remove_space_and_ears(char ***cmd, char **tokens, char **str)
{
	if (ft_strlen((*tokens)) == 0)
	{
		if ((*str))
		{
			(*cmd) = realloc_and_add((*cmd), (*str));
			free((*str));
			(*str) = NULL;
		}
	}
	else
	{
		if (remove_ears(tokens) == 1)
			(*tokens) = append_line((*tokens), " ");
		(*str) = append_line((*str), (*tokens));

	}
}

char	**cut_cmds(int *find_cmd, char **tokens)
{
	int		i;
	char	**cmd;
	char	*str;

	find_next_pipe(tokens, find_cmd);
	if (find_cmd[0] > find_cmd[1])
		return (NULL);
	i = find_cmd[0];
	cmd = NULL;
	str = NULL;
	while (i < find_cmd[1])
	{
		remove_space_and_ears(&cmd, &tokens[i], &str);
		i++;
	}
	if (str)
	{
		cmd = realloc_and_add(cmd, str);
		free(str);
	}
	return (cmd);
}

int	parser(t_input *data)
{
	t_list	*head;
	t_list	*node;
	int		find_cmd[2];
	char	**cmd;
	
	find_cmd[0] = 0;
	find_cmd[1] = 0;
	cmd = cut_cmds(find_cmd, data->tokens);
	head = new_list_cmd(cmd);
	while (data->tokens[find_cmd[1]])
	{
		cmd = cut_cmds(find_cmd, data->tokens);
		node = new_list_cmd(cmd);
		ft_lstadd_back(&head, node);
	}
	free_2darray(data->tokens);
	data->cmds = head;
	return (0);
}

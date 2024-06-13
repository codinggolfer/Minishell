/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:07 by halgordziba       #+#    #+#             */
/*   Updated: 2024/06/13 23:20:05 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// if (!ft_strncmp(tokens[find_cmd[1]], "|", ft_strlen(tokens[find_cmd[1]])))
	// 	find_cmd[1]++;
	// while (tokens)
	// {
	// 	if (!ft_strncmp(tokens[find_cmd[1]], "|", ft_strlen(tokens[find_cmd[1]])))

int	find_next_pipe(char **tokens, int *find_cmd)
{
	if (!ft_strncmp(tokens[find_cmd[1]], "|", ft_strlen(tokens[find_cmd[1]])))
		find_cmd[1]++;
	find_cmd[0] = find_cmd[1];
	while (tokens)
	{
		if (!ft_strncmp(tokens[find_cmd[1]], "|", ft_strlen(tokens[find_cmd[1]])))
			break ;
		find_cmd[1]++;
		tokens++;
	}
	//printf("in the find pipe %d\n", find_cmd[1]);
	return(0);
}

int	remove_ears(char **tokens)
{
	int	ret_val;
	int	i;

	ret_val = ((*tokens)[0] == '\"' || (*tokens)[0] == '\'');
	i = 0;
	if ((*tokens)[0] == '\"')
		(*tokens) = ft_strtrim((*tokens), "\"");
	else if ((*tokens)[0] == '\'')
		(*tokens) = ft_strtrim((*tokens), "\'");
	++i;
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
		if (remove_ears(tokens) == 0)
			(*tokens) = ft_strtrim((*tokens), " ");
		(*str) = append_line((*str), (*tokens));
	}
}

char	**cut_cmds(int *find_cmd, char **tokens)	
{
	int		i;
	char	**cmd;
	char	*str;
	
	find_next_pipe(tokens, find_cmd);
	i = find_cmd[0];
	cmd = NULL;
	str = NULL;
	//printf("in the find cut cmds %d\n", find_cmd[1]);
	//printf("in the find cut cmds %d\n", find_cmd[0]);
	while (i < find_cmd[1])
	{
		remove_space_and_ears(&cmd, &tokens[i], &str);
		i++;
	}
	//printf("%s\n", str);
	if (str)
	{
		cmd = realloc_and_add(cmd, str);
		free(str);
	}
	return (cmd);
}

int	parser(t_input *data)
{
	t_list	*ret;
	t_list	*node;
	int		find_cmd[2];
	char	**cmd;

	find_cmd[1] = 0;
	cmd = cut_cmds(find_cmd, data->tokens);
	return (0);
}


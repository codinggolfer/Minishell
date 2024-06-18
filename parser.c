/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:07 by halgordziba       #+#    #+#             */
/*   Updated: 2024/06/18 16:09:12 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	printf("tokens from rm earss %c\n", (*tokens)[0]);
	ret_val = ((*tokens)[0] == '\"' || (*tokens)[0] == '\'');
	if ((*tokens)[0] == '\"')
		(*tokens) = ft_strtrim((*tokens), "\"");
	else if ((*tokens)[0] == '\'')
		(*tokens) = ft_strtrim((*tokens), "\'");
	printf("tokens from rm earss bottom %s\n", (*tokens));
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
	if (find_cmd[0] > find_cmd[1])
		return (NULL);
	i = find_cmd[0];
	cmd = NULL;
	str = ft_strdup("");
	//printf("in the find cut cmds %d\n", find_cmd[1]);
	//printf("in the find cut cmds %d\n", find_cmd[0]);
	printf("%s\n", tokens[0]);
	while (i < find_cmd[1])
	{
		remove_space_and_ears(&cmd, &tokens[i], &str);
		printf("%s\n", str);
		i++;
	}
	printf("%s\n", cmd[0]);
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

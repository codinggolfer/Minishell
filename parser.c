/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:07 by halgordziba       #+#    #+#             */
/*   Updated: 2024/06/25 16:52:38 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_next_pipe(char **tokens, int *find_cmd)
{
	if (!ft_strcmp(tokens[find_cmd[1]], "|"))
		find_cmd[1]++;
	if (ft_strcmp(tokens[find_cmd[1]], "|") == 1)
		find_cmd[1]++;
	find_cmd[0] = find_cmd[1];
	while (tokens[find_cmd[1]])
	{
		//printf("the token in find pipe %s\n", tokens[find_cmd[1]]);
		if (!ft_strcmp(tokens[find_cmd[1]], "|"))
			break ;
		// printf("in the find pipe %d\n", find_cmd[1]);
		// printf("here1\n");
		find_cmd[1]++;
		printf(" int the counter %d\n", find_cmd[1]);
	}
}

int	remove_ears(char **tokens)
{
	int	ret_val;

	//printf("tokens from rm earss %c\n", (*tokens)[0]);
	ret_val = ((*tokens)[0] == '\"' || (*tokens)[0] == '\'');
	if ((*tokens)[0] == '\"')
	{
		(*tokens) = ft_strtrim((*tokens), "\"");
	}
	else if ((*tokens)[0] == '\'')
		(*tokens) = ft_strtrim((*tokens), "\'");
	//printf("tokens from rm earss bottom %s\n", (*tokens));
	return (ret_val);
}

void	remove_space_and_ears(char ***cmd, char **tokens, char **str)
{
	if (ft_strlen((*tokens)) == 0)
	{
		if ((*str))
		{
			printf("in the realloc and add: %s\n", (*str));
			(*cmd) = realloc_and_add((*cmd), (*str));
			free((*str));
			(*str) = ft_strdup("");
			printf("cmd in rm spa and erars: %s\n", *cmd[0]);
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

	//printf("here1\n");
	find_next_pipe(tokens, find_cmd);
	//printf("here\n");
	if (find_cmd[0] > find_cmd[1])
		return (NULL);
	i = find_cmd[0];
	cmd = NULL;
	str = ft_strdup("");
	//printf("in the find cut cmds %d\n", find_cmd[1]);
	//printf("in the find cut cmds %d\n", find_cmd[0]);
	//printf("%s\n", tokens[0]);
	while (i < find_cmd[1])
	{
		printf("tokens int the while loop: %s\n", tokens[i]);
		remove_space_and_ears(&cmd, &tokens[i], &str);
		//printf("%s\n", str);
		i++;
	}
	// printf("the cmd: %s\n", cmd[5]);
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
	t_list	*head;
	t_list	*node;
	int		find_cmd[2];
	char	**cmd;
	
	for (int i = 0; data->tokens[i] != NULL; i++)
		printf("%s\n", data->tokens[i]);
	printf("\n");
	find_cmd[1] = 0;
	cmd = cut_cmds(find_cmd, data->tokens);
	head = new_list_cmd(cmd);
	while (data->tokens[find_cmd[1]])
	{
		//printf("here\n");
		cmd = cut_cmds(find_cmd, data->tokens);
		node = new_list_cmd(cmd);
		ft_lstadd_back(&head, node);
	}
	printf("first cmd in rm spa and erars: %s\n", head->cmd.cmd[0]);
	printf("secound cmd in rm spa and erars: %s\n", head->next->cmd.cmd[0]);
	printf("secound cmd in rm spa and erars: %s\n", head->next->next->cmd.cmd[0]);
	// printf("cmd in rm spa and erars: %s\n", cmd[2]);
	free_2darray(data->tokens);
	return (0);
}

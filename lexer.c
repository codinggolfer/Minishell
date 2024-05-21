/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:43:29 by halgordziba       #+#    #+#             */
/*   Updated: 2024/05/21 15:37:24 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_token(char *line, int token_type, int i)
{
	if (line[i + 1] && (token_type == 4 || token_type == 5))
		if (token_type == is_token(line[i + 1]))
			i++;
	else if (token_type == 1 || token_type == 2)
		i = bunny_ears(line, i, line[i]);
}

int	find_token_pos(char *line, int *token_pos)
{
	int	i;
	int	token_type;
	
	if(!line)
		return(-1);
	i = token_pos[1] + 1;
	while (line[i] && line[i] == ' ')
		i++;
	token_pos[0] = i;
	token_type = is_token(line[i]);
	if (token_type)
		i = handle_token(line, token_type, i);
	else
	{
		while (line[i] && !is_token(line[i] && line[i] != ' '))
			i++;
		i--;
	}
	token_pos[1] = i;
	return (token_type);
}

void	add_spaces(t_input *data, int ret_val, int *token_pos)
{
	if (ret_val > 0)
	{
		if (ret_val == 1 || ret_val == 2)
		{
			if (data->line[token_pos[1] + 1] == ' ')
			{
				data->tokens = realloc_and_add(data->tokens, "");
				++token_pos[1];
			}
		}
		else if (ret_val == 4 || ret_val == 5)
			data->tokens = realloc_and_add(data->tokens, "");
	}
	else if (data->line[token_pos[1] + 1] == ' ')
		data->tokens = realloc_and_add(data->tokens, "");
}


int	lexer(t_input *data)
{
	int		len;
	int		token_pos[2];
	int		ret_val;
	char	*new_token;

	len = ft_strlen(data->line);
	data->tokens = (char **) malloc(sizeof(char *));
	if (!data->tokens)
		return(0);
	token_pos[1] = 0;
	data->tokens[0] = NULL;
	while (1)
	{
		ret_val = find_token_pos(data->line, token_pos);
		if (ret_val == -1)
			break;
		new_token = ft_substr(data->line, token_pos[0], token_pos[1]);
		data->tokens = realloc_and_add(data->tokens, new_token);
		add_spaces(data, ret_val, token_pos);
		free(new_token);
	}
	return (1);
}
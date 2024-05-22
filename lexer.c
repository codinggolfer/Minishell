/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:43:29 by halgordziba       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/17 14:48:11 by hzibari          ###   ########.fr       */
=======
/*   Updated: 2024/05/21 15:37:24 by halgordziba      ###   ########.fr       */
>>>>>>> bced92b4eff3bca0c5fc88f4fe65b01410f5db8c
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
		i = handle_token(line, token_type, i);  //TODO
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
	int		i;
	int		len;
	int		token_pos[2];
	int		ret_val;
	char	*new_token;

	i = 0;
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
<<<<<<< HEAD
		data->tokens[i] = ft_substr(data->line, token_pos[0], token_pos[1] - token_pos[0]);
		
=======
		new_token = ft_substr(data->line, token_pos[0], token_pos[1]);
		data->tokens = realloc_and_add(data->tokens, new_token);
		add_spaces(data, ret_val, token_pos);
		free(new_token);
>>>>>>> bced92b4eff3bca0c5fc88f4fe65b01410f5db8c
	}
	return (1);
}
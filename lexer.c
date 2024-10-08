/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:43:29 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/22 16:17:29 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_handler(char *line, int token_type, int i)
{
	if (line[i] != '\0' && (token_type == 3
			|| token_type == 4 || token_type == 5))
	{
		if (token_type == is_token(line[i + 1]))
			i++;
		i++;
	}
	else if (token_type == 1 || token_type == 2)
	{
		i = bunny_ears(line, i, line[i]);
	}
	return (i);
}

int	find_pos(char *line, int *pos)
{
	int	i;
	int	token_type;

	if (!line || !line[pos[1]])
		return (-1);
	i = pos[1];
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	pos[0] = i;
	token_type = is_token(line[i]);
	if (token_type)
		i = token_handler(line, token_type, i);
	else
	{
		while (line[i] && !is_token(line[i]) && line[i] != ' ')
			i++;
	}
	pos[1] = i;
	return (token_type);
}

void	add_spaces(t_input *data, int ret, int *pos)
{
	if (ret > 0)
	{
		if (ret == 1 || ret == 2)
		{
			if (data->line[pos[1]] == ' ')
			{
				data->tokens = realloc_and_add(data->tokens, "");
				++pos[1];
			}
		}
		else if (ret == 4 || ret == 5)
			data->tokens = realloc_and_add(data->tokens, "");
	}
	else if (data->line[pos[1]] == ' ')
		data->tokens = realloc_and_add(data->tokens, "");
}

int	lexer(t_input *data)
{
	int		pos[2];
	int		ret;
	char	*new_tkn;

	data->tokens = (char **) ft_calloc(sizeof(char *), 1);
	if (!data->tokens)
		return (0);
	pos[1] = 0;
	data->tokens[0] = NULL;
	while (1)
	{
		ret = find_pos(data->line, pos);
		if (ret == -1)
			break ;
		if (ret == 3 || ret == 4 || ret == 5)
			data->tokens = realloc_and_add(data->tokens, "");
		new_tkn = ft_substr(data->line, pos[0], pos[1] - pos[0]);
		data->tokens = realloc_and_add(data->tokens, new_tkn);
		add_spaces(data, ret, pos);
		free(new_tkn);
	}
	return (1);
}

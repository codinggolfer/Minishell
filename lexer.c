/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:43:29 by halgordziba       #+#    #+#             */
/*   Updated: 2024/05/17 14:48:11 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token_pos(char *line, int *token_pos)
{
	int	i;
	int	token_type;
	
	if(!line)
		return(-1);
	i = 0;
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
		data->tokens[i] = ft_substr(data->line, token_pos[0], token_pos[1] - token_pos[0]);
		
	}
}
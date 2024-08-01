/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:40:44 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/01 15:56:55 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	int		i;
	char	token[6];

	i = 0;
	token[0] = '\'';
	token[1] = '\"';
	token[2] = '|';
	token[3] = '>';
	token[4] = '<';
	token[5] = '\0';
	while (token[i])
	{
		if (token[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

int	bunny_ears(char *line, int start, int bunny_ears)
{
	start++;
	while (line[start] && line[start] != bunny_ears)
		start++;
	if (!line[start])
		return (-1);
	start++;
	return (start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:40:44 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/14 15:08:32 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char c)
{
	if (c == 39 || c == 34 || c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

int	bunny_ears(char *line, int stop, int bunny_ears)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (start < stop && line[start] != bunny_ears && line[start])
		start++;
	end = start;
	while (end < stop && line[end] != bunny_ears && line[end])
		end++;
	

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:40:44 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/17 14:10:05 by hzibari          ###   ########.fr       */
=======
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:40:44 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/18 23:06:43 by halgordziba      ###   ########.fr       */
>>>>>>> bced92b4eff3bca0c5fc88f4fe65b01410f5db8c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
<<<<<<< HEAD
	end = start;
	while (end < stop && line[end] != bunny_ears && line[end])
		end++;

}
=======
	if (!line[start])
		return (-1);
	return (start);
}
>>>>>>> bced92b4eff3bca0c5fc88f4fe65b01410f5db8c

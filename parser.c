/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:27:07 by halgordziba       #+#    #+#             */
/*   Updated: 2024/06/11 15:06:47 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_cmds(int *find_cmd, char **tokens)	
{
	
}

int	parser(t_input *data)
{
	t_list	*ret;
	t_list	*node;
	int		find_cmd[2];
	char	**cmd;

	find_cmd[1] = 0;
	cmd = cut_cmds(find_cmd, data->tokens);
}


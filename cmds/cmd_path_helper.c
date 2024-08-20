/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:43:03 by halgordziba       #+#    #+#             */
/*   Updated: 2024/08/19 21:00:18 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_executable(char *str)
{
	if (ft_strlen(str) > 2 && str[0] == '.' && str[1] == '/')
		return (1);
	return (0);
}

int	is_absolute(char *str)
{
	if (ft_strlen(str) > 2 && str[0] == '/')
		return (1);
	return (0);
}

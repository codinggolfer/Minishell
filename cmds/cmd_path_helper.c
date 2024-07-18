/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:43:03 by halgordziba       #+#    #+#             */
/*   Updated: 2024/07/18 13:43:26 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
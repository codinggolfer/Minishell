/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:12:27 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/18 14:51:54 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1[i] || !s2[i])
        return (1);
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (2);
        i++;
    }
    return (0);
}

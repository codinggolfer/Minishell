/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:50:46 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/01 15:54:27 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_keywords(char *line, int stop)
{
    stop++;
    while (line[stop] && line[stop] != ' ' && !is_token(line[stop]) && line[stop] != '$')
        stop++;
    return (stop--);
}
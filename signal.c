/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:58 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/22 14:09:22 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newliner(int signal)
{
	(void) signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "", 1);
	rl_redisplay();
}

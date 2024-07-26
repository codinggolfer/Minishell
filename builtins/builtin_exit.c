/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:52 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/23 15:29:24 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_number(char *num)
{
	int	i;

	i = 0;
	if (!num[0])
		return (0);
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int builtin_exit(t_input *data, char **arg)
{
    int ecode;

    printf("exit\n");
    if (count_arg_array(arg) > 2)
        return (error_msg("exit", NULL, "too many arguments", 1));
    else if (arg[1] == NULL)
        ecode = 0;
    else if (is_number(arg[1]) == 0)
        ecode = error_msg("exit", arg[1], "numeric argument required", 2);
    else
        ecode = ft_atoi(arg[1]);
    while (ecode >= 256)
        ecode -= 256;
    tcsetattr(STDIN_FILENO, TCSANOW, data->old);
    return (ecode);
}
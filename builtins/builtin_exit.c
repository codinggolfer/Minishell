/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:52 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/09 15:15:29 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long	ft_atol(const char *str)
{
	long		mp;
	long		number;

	mp = 1;
	number = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			mp *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str++ - '0';
	}
	if (number * mp > 2147483647 || number * mp < -2147483648)
		return (number * mp);
	if (number == 0 && mp == -1)
        return (number * mp);
	return (number * mp);
}

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
    else if (is_number(arg[1]) == 0 || ft_atol(arg[1]) > INT_MAX || ft_atol(arg[1]) < INT_MIN)
        ecode = error_msg("exit", arg[1], "numeric argument required", 2);
    else
        ecode = ft_atoi(arg[1]);
    while (ecode >= 256)
        ecode -= 256;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->new);
    exit (0);
	//exit (reset_exit(&data->atr->def_atr, ecode));
}
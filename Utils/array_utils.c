/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:50:27 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/06 13:36:46 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

void	free_2darray(char **array)
{
	int	i;
	int	len;

	i = 0;
	if (!array)
		return ;
	len = count_arg_array(array);
	while (i < len)
	{
		free (array[i]);
		i++;
	}
	array[0] = NULL;
}

char	**realloc_and_add(char **src, char *str)
{
	int		i;
	int		len;
	char	**ret;

	i = 0;
	len = count_arg_array(src);
	ret = ft_calloc(sizeof(char *), len + 2);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = ft_strdup(src[i]);
		i++;
	}
	ret[i] = ft_strdup(str);
	free_2darray(src);
	return (ret);
}

int	find_symbol(char *line, int found)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] == found)
			return (i);
		i++;
	}
	return (-1);
}

int	strcmp_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	if (s1[i] == '=' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}
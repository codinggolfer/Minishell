/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:12:27 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/22 20:26:00 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr2(char const *s, unsigned int start, unsigned int end)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s && start > end)
		return (0);
	if (end >= (unsigned int) ft_strlen(s))
		end = ft_strlen(s);
	if (start >= (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	substr = (char *)malloc((end - start) + 2 * sizeof(char));
	if (!substr)
		return (NULL);
	while (start <= end && s[start] != '\0')
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strtrim2(char *s1, char set)
{
	char	*trimstr;
	int		start;
	int		end;

	start = 0;
	trimstr = NULL;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (s1[start] && s1[start] == set)
		start++;
	if (s1[start] == '\0')
		trimstr = ft_strdup("");
	else
	{
		while (end >= 0 && s1[end] == set)
			end--;
		trimstr = ft_substr2(s1, start, end);
	}
	free(s1);
	return (trimstr);
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (!(!s1 && !s2));
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		++i;
	}
	return (s1[i] - s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (2);
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

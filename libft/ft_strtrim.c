/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:24:24 by eagbomei          #+#    #+#             */
/*   Updated: 2024/06/19 15:32:54 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	char	*trimstr;
	int		start;
	int		end;
	int		len;
	int		len2;

	start = 0;
	end = 0;
	if (s1 == 0 || set == 0)
		return (0);
	len = ft_strlen(s1) - 1;
	len2 = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && start <= len)
		start++;
	if (start >= len)
		return (free(s1), trimstr = ft_strdup(""));
	while (ft_strchr(set, s1[len]) != 0)
	{
		end++;
		len--;
	}
	trimstr = ft_substr(s1, start, len2 - start - end);
	free(s1);
	return (trimstr);
}

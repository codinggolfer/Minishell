/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:29:51 by eagbomei          #+#    #+#             */
/*   Updated: 2024/06/18 15:58:34 by hzibari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	nstr = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (nstr == 0)
		return (0);
	while ((char)s1[i] != '\0')
	{
		nstr[i] = s1[i];
		i++;
	}
	while ((char)s2[j] != '\0')
	{
		nstr[i] = s2[j];
		i++;
		j++;
	}
	nstr[i] = '\0';
	return (nstr);
}

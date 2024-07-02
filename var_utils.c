/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:59:49 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/02 15:42:42 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int break_down(char *ret, int *index, char **str)
{
    index[2] = get_keywords(ret, index[1]);
    if (index[0] != index[1])
        str[0] = ft_substr(ret, index[0], index[1] - 1);
    else
        str[0] = NULL;
    str[1] = ft_substr(ret, index[1]+ 1, index[2]);
    str[2] = ft_substr(ret, index[2] + 1, ft_strlen(ret));
    return (index[2] == index[1]);
}

void    innit_rd_vars(int *spec, int *index, char **str)
{
    *spec = 0;
    index[0] = 0;
    index[1] = 0;
    index[2] = 0;
    str[4] = NULL;
}

char    *handle_special(char *line, int end, int special)
{
    int left;
    int right;

    left = (line[end - 1] != '\'' && line[end - 1] != '\"');
    if (!special)
        right = (line[end + 1] == '\'' || line[end + 1] == '\"');
    else
        right = (!is_token(line[end + 1]) && line[end + 1] != ' ');
    if (left && right)
       return(ft_strdup(""));
    else
        return (ft_strdup("$"));
}
void    get_return(char **buff, char **str, int *index)
{
    int     i;
    char    *ret;

    i = 0;
    if ((*buff))
        free ((*buff));
    ret = NULL;
    ret = ft_strjoin(ret, str[0]);
    printf("%s\n", ret);
    ret = ft_strjoin(ret, str[3]);
   // ret = ft_strjoin(ret, str[2]);
    (*buff) = ret;
    index[1] = ft_strlen(str[0]) + ft_strlen(str[3]) - 1;
    while (str[i])
    {
        free (str[i]);
        i++;
    }
}

void dollar_sign(t_input *data)
{
    int     special;
    int     index[3];
    char    *ret;
    char    *str[5];

    innit_rd_vars(&special, index, str);
    ret = ft_strdup(data->line);
    while (find_symbol(&ret[index[1]], '$') != -1)
    {
        if (ret[index[1]] == '\"')
            special = !special;
        else if (ret[index[1]] == '\'' && !special)
            index[1] = bunny_ears(ret, index[1], '\'');
        else if (ret[index[1]] == '$')
        {
            if (break_down(ret, index, str))
               str[3] = handle_special(ret, index[2], special);
            else
                str[3] = access_var(data, str[1]);
            get_return(&ret, str, index);
        }
        index[1]++;
    }
    free(data->line);
    data->line = ret;
}
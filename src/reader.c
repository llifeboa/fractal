/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 04:06:06 by llifeboa          #+#    #+#             */
/*   Updated: 2019/10/16 05:10:06 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char    *read_command(char *file)
{
    char    *result;
    int     fd;
    char    *line;
    char    *temp;

    temp = 0;
    result = 0;
    fd = open(file, O_RDONLY);
    while (get_next_line(fd, &line))
    {
        temp = result;
        if (temp == 0)
        {
            temp = line;
            line = 0;
            result = temp;
        }
        else
        {
            result = ft_strjoin(temp, line);
            free(line);
            free(temp);
        }
    }
    return (result);
}

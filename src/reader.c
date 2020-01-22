/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 04:06:06 by llifeboa          #+#    #+#             */
/*   Updated: 2020/01/22 20:11:14 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char		*read_command(char *file, int fd)
{
	char	*result;
	char	*line;
	char	*temp;

	temp = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if ((temp = result) == 0)
		{
			temp = line;
			line = 0;
			result = ft_strjoin(temp, "\n");
		}
		else
		{
			temp = ft_strjoin(result, "\n");
			free(result);
			result = ft_strjoin(temp, line);
			free(line);
		}
		free(temp);
	}
	free(line);
	return (result);
}

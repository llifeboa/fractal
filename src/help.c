/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:41:00 by llifeboa          #+#    #+#             */
/*   Updated: 2020/01/22 17:51:29 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exit_with_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(0);
}

void	malloc_check(void *data)
{
	if (data == NULL)
		exit_with_error("malloc_err");
}

int		check_fract_type(char *fract_type)
{
	if (!ft_strcmp(fract_type, "mandelbrot"))
		return (MANDELBROT);
	else if (!ft_strcmp(fract_type, "julia"))
		return (JULIA);
	else if (!ft_strcmp(fract_type, "burning_ship"))
		return (BURNING_SHIP);
	else
		return (-1);
}

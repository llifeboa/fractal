/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:41:00 by llifeboa          #+#    #+#             */
/*   Updated: 2019/10/13 19:20:24 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    exit_with_error(char *message)
{
    ft_putstr_fd(message, 2);
    exit(0);
}

void    malloc_check(void *data)
{
    if(data == NULL)
        exit_with_error("malloc_err");
}

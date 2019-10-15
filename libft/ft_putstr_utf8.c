/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_utf8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:21:17 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/11 23:21:21 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_utf8(int *c, int fd)
{
	int i;

	i = 0;
	while (c[i])
	{
		ft_putchar_utf8(c[i], fd);
		i++;
	}
}
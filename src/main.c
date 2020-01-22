/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:14:41 by llifeboa          #+#    #+#             */
/*   Updated: 2020/01/22 18:55:45 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			mouse_move(int x, int y, void *param)
{
	t_main *m;

	m = (t_main*)param;
	if (m->shift_press == 1)
	{
		m->x_param = (double)x / ((double)WIDTH / 2) - 1;
		m->y_param = (double)y / ((double)HEIGHT / 2) - 1;
		update(m);
	}
	return (0);
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_main	*m;
	short	sign;

	m = (t_main *)param;
	if (button == 4 || button == 5)
	{
		sign = button == 4 ? 1 : -1;
		m->step = (m->y_max - m->y_min) / 100 * 3;
		if (m->y_max - m->y_min - m->step * sign >
		EPS && m->y_max - m->y_min - m->step * sign < 4)
		{
			m->max_iter += sign;
			m->x_min = m->x_min + (double)x / WIDTH *
			m->step * sign * m->mouse_delta;
			m->x_max = m->x_max - (double)(WIDTH - x) /
			WIDTH * m->step * sign * m->mouse_delta;
			m->y_min = m->y_min + (double)y / HEIGHT *
			m->step * sign;
			m->y_max = m->y_max - (double)(HEIGHT - y) /
			HEIGHT * m->step * sign;
			update(m);
		}
	}
	return (0);
}

int			keypress(int key, void *param)
{
	t_main *m;

	m = (t_main *)param;
	if (key == 257)
		m->shift_press = m->shift_press > 0 ? 0 : 1;
	else if (key >= 18 && key <= 20)
	{
		m->color = key - 18;
		update(m);
	}
	else if (key == 53)
		exit(0);
	else if (key == 49)
	{
		reinit(m);
		update(m);
	}
	return (0);
}

void		controls(t_main *m)
{
	mlx_hook(m->win, 3, 0, keypress, m);
	mlx_hook(m->win, 6, 0, mouse_move, m);
	mlx_mouse_hook(m->win, mouse_press, m);
}

int			main(int argc, char *argv[])
{
	t_main	*m;
	int		frac_type;
	char	*kernels[3];

	kernels[0] = "mandelbrot";
	kernels[1] = "julia";
	kernels[2] = "burning";
	if (argc != 2)
	{
		ft_putstr("using: fractol mandelbrot | julia | burning_ship");
		return (0);
	}
	frac_type = check_fract_type(argv[1]);
	if (frac_type == -1)
	{
		ft_putstr("using: fractol mandelbrot | julia | burning_ship");
		return (0);
	}
	m = init(frac_type);
	settings(m, kernels[m->frac_type]);
	update(m);
	controls(m);
	mlx_loop(m->ptr);
	return (0);
}

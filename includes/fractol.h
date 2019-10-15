/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:15:32 by llifeboa          #+#    #+#             */
/*   Updated: 2019/10/15 08:01:03 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WG_SIZE 256
# define WIDTH 1920
# define HEIGHT 1020
# define MANDELBROTFILE "./src/mandelbrot.cl"

# include <stdlib.h>
# include <OpenCL/opencl.h>
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_main
{
	void				*ptr;
	void				*win;
	int					iterations;
	double				x_min;
	double				x_max;
	double				y_min;
	double				y_max;
	cl_int				err;
    cl_uint				num_platforms;
    cl_platform_id		platform;
    cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				memobj;
	cl_int				*mem;
	int					memLenth;
	size_t 				global_work_size;
	void				*image;
	char	   			*image_data;
	int     			bpp;
	int     			size_line;
	int     			endian;
	const char			*command;
	int					color;
	double				step;
	double				mouse_delta;


}					t_main;

void    malloc_check(void *data);
void    exit_with_error(char *message);
t_main  *init();

#endif
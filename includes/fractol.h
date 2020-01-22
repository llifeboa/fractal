/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:15:32 by llifeboa          #+#    #+#             */
/*   Updated: 2020/01/22 20:11:35 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MANDELBROT 0
# define JULIA 1
# define BURNING_SHIP 2
# define EPS 0.0000000000001
# define HEIGHT 1080
# define WIDTH 1920

# include "libft.h"
# include <stdlib.h>
# include <OpenCL/opencl.h>
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct			s_main
{
	void				*ptr;
	void				*win;
	int					iterations;
	double				x_min;
	double				x_max;
	double				y_min;
	double				y_max;
	int					max_iter;
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
	int					mem_length;
	size_t				global_work_size;
	void				*image;
	char				*image_data;
	int					bpp;
	int					size_line;
	int					endian;
	const char			*command;
	int					color;
	double				step;
	double				mouse_delta;
	short				shift_press;
	double				x_param;
	double				y_param;
	int					frac_type;

}						t_main;

void					settings(t_main *m, char *k);
t_main					*init(int frac_type);
void					*reinit(t_main *res);
void					update(t_main *m);
char					*read_kernel(void);
void					malloc_check(void *data);
void					exit_with_error(char *message);
int						check_fract_type(char *fract_type);
t_main					*init(int frac_type);
char					*read_command(char *file, int fd);
#endif

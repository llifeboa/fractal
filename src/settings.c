/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:26:23 by llifeboa          #+#    #+#             */
/*   Updated: 2020/01/22 20:11:46 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		settings(t_main *m, char *k)
{
	m->err = clGetPlatformIDs(1, &(m->platform),
	&(m->num_platforms));
	m->err = clGetDeviceIDs((m->platform), CL_DEVICE_TYPE_GPU,
	1, &(m->device_id), NULL);
	m->context = clCreateContext(NULL, 1, &(m->device_id),
	NULL, NULL, &(m->err));
	m->command_queue = clCreateCommandQueue(m->context,
	(m->device_id), 0, &(m->err));
	m->program = clCreateProgramWithSource(m->context, 1,
	&(m->command), NULL, &(m->err));
	m->err = clBuildProgram(m->program, 1,
	&(m->device_id), NULL, NULL, NULL);
	m->kernel = clCreateKernel(m->program,
	k, &(m->err));
	m->mem_length = HEIGHT * WIDTH;
	m->global_work_size = WIDTH * HEIGHT;
	m->mem = (cl_int *)m->image_data;
	m->memobj = clCreateBuffer(m->context, CL_MEM_READ_WRITE,
	m->mem_length * sizeof(cl_int), NULL, &(m->err));
	m->err = clSetKernelArg(m->kernel, 0, sizeof(cl_mem), (void *)&(m->memobj));
}

t_main		*init(int frac_type)
{
	t_main	*res;

	malloc_check(res = (t_main*)malloc(sizeof(t_main)));
	res->x_min = -2;
	res->x_max = 2;
	res->y_min = -1;
	res->y_max = 1;
	res->max_iter = 512;
	res->mouse_delta = (res->x_max - res->x_min) / (res->y_max - res->y_min);
	res->step = 0.01f;
	res->ptr = mlx_init();
	res->win = mlx_new_window(res->ptr, WIDTH, HEIGHT, "best fractol");
	res->image = mlx_new_image(res->ptr, WIDTH, HEIGHT);
	res->image_data = mlx_get_data_addr(res->image,
	&(res->bpp), &(res->size_line), &(res->endian));
	res->command = read_command("src/fractals.cl", 0);
	res->shift_press = 0;
	res->x_param = -0.8;
	res->y_param = 0;
	res->color = 0;
	res->frac_type = frac_type;
	return (res);
}

void		*reinit(t_main *res)
{
	res->x_min = -2;
	res->x_max = 2;
	res->y_min = -1;
	res->y_max = 1;
	res->max_iter = 512;
	res->mouse_delta = (res->x_max - res->x_min) / (res->y_max - res->y_min);
	res->step = 0.01f;
	return (res);
}

void		update(t_main *m)
{
	mlx_clear_window(m->ptr, m->win);
	m->err = clSetKernelArg(m->kernel, 1, sizeof(m->x_min), &(m->x_min));
	m->err = clSetKernelArg(m->kernel, 2, sizeof(m->x_max), &(m->x_max));
	m->err = clSetKernelArg(m->kernel, 3, sizeof(m->y_min), &(m->y_min));
	m->err = clSetKernelArg(m->kernel, 4, sizeof(m->y_max), &(m->y_max));
	m->err = clSetKernelArg(m->kernel, 5, sizeof(m->max_iter), &(m->max_iter));
	m->err = clSetKernelArg(m->kernel, 6, sizeof(double), &(m->x_param));
	m->err = clSetKernelArg(m->kernel, 7, sizeof(double), &(m->y_param));
	m->err = clSetKernelArg(m->kernel, 8, sizeof(int), &(m->color));
	m->err = clEnqueueNDRangeKernel(m->command_queue, m->kernel,
	1, NULL, &(m->global_work_size), NULL, 0, NULL, NULL);
	m->err = clEnqueueReadBuffer(m->command_queue, m->memobj,
	CL_TRUE, 0, m->mem_length * sizeof(cl_int), m->mem, 0, NULL, NULL);
	clFinish(m->command_queue);
	mlx_put_image_to_window(m->ptr, m->win, m->image, 0, 0);
}

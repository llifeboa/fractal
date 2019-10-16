/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:14:41 by llifeboa          #+#    #+#             */
/*   Updated: 2019/10/16 08:07:52 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double current, double end, double new_start, double new_end)
{
	return (current / end * (new_end - new_start) + new_start);
}

void	calculate(int *image, t_main *data)
{
	for (int i = 0; i < 1080; i ++)
	{
		for (int j = 0; j < 1920; j++)
		{
			double x_z = map(j, 1920, -2.5, 1);
			double y_z = map(i, 1080, -1, 1);
			double x = 0;
			double y = 0;
			int iter = 0;
			double x_temp;
			while (x*x + y*y <= 4 && iter < 256)
			{
				x_temp = x*x - y*y + x_z;
				y = 2*x*y + y_z;
				x = x_temp;
				iter++;
			}
			if (iter == 256)
			{
				image[i * 1920 + j] = 0;
			}
			else
			{
				image[i * 1920 + j] = iter;
			}
			
		}
	}
}

char    *read_kernel()
{
	char    res1[2500];
	char    *current_line;
	char    *temp;
	int     fd;
	int		ret;

//	res1 = ft_strnew(3000);
	fd = open(MANDELBROTFILE, O_RDONLY);
	ret = read(fd, res1, 2500);
	return (res1);
}

t_main  *init()
{
	t_main  *res;
	res = (t_main*)malloc(sizeof(t_main));
	res->x_min = -2.5;
	res->x_max = 1;
	res->y_min = -1;
	res->y_max = 1;
	res->max_iter = 256;
	res->mouse_delta = (res->x_max - res->x_min) / (res->y_max - res->y_min);
	res->step = 0.01f;
	res->ptr = mlx_init();
	res->win = mlx_new_window(res->ptr, WIDTH, HEIGHT, "best fractol");
	res->image = mlx_new_image(res->ptr, WIDTH, HEIGHT);
	res->image_data = mlx_get_data_addr(res->image, &(res->bpp), &(res->size_line), &(res->endian));
	res->command = read_command("src/mandelbrot.cl");
	return res;

}
int mouse_press(int button, int x, int y, void *param)
{
	t_main *main_data;
	short sign;
	
	main_data = (t_main *)param;
	if (button == 4 || button == 5)
	{
		
		sign = button == 4 ? 1 : -1;
		main_data->max_iter += sign;
		main_data->max_iter *= 80;
		main_data->step = (main_data->y_max - main_data->y_min) / 100 * 5;
		main_data->x_min = main_data->x_min + (double)x / WIDTH * main_data->step * sign * main_data->mouse_delta;
		main_data->x_max = main_data->x_max - (double)(WIDTH - x) / WIDTH * main_data->step * sign * main_data->mouse_delta;
		main_data->y_min = main_data->y_min + (double)y / HEIGHT * main_data->step * sign;
		main_data->y_max  = main_data->y_max - (double)(HEIGHT - y) / HEIGHT * main_data->step * sign;
		mlx_clear_window(main_data->ptr,main_data->win);
		main_data->err = clSetKernelArg(main_data->kernel, 1, sizeof(main_data->x_min), &(main_data->x_min));
		main_data->err = clSetKernelArg(main_data->kernel, 2, sizeof(main_data->x_max), &(main_data->x_max));
		main_data->err = clSetKernelArg(main_data->kernel, 3, sizeof(main_data->y_min), &(main_data->y_min));
		main_data->err = clSetKernelArg(main_data->kernel, 4, sizeof(main_data->y_max), &(main_data->y_max));
		main_data->err = clSetKernelArg(main_data->kernel, 5, sizeof(main_data->max_iter), &(main_data->max_iter));
		main_data->err = clEnqueueNDRangeKernel(main_data->command_queue, main_data->kernel, 1, NULL, &(main_data->global_work_size), NULL, 0, NULL, NULL);
		main_data->err = clEnqueueReadBuffer(main_data->command_queue, main_data->memobj, CL_TRUE, 0, main_data->memLenth * sizeof(cl_int), main_data->mem, 0, NULL, NULL);
		clFinish(main_data->command_queue);
		mlx_put_image_to_window(main_data->ptr, main_data->win, main_data->image, 0, 0);
	}
	
	return (0);
}

int			keypress(int key, void *param)
{
	t_main *main_data;
	
	main_data = (t_main *)param;
	if (key == 69)
		{
			
		}
}

void		controls(t_main *main_data)
{
	mlx_hook(main_data->win, 2, 0, keypress, main_data);
	mlx_mouse_hook(main_data->win, mouse_press, main_data);
}

int main(int argc, char const *argv[])
{
	t_main *main_data;

	main_data = init();

	main_data->err = clGetPlatformIDs(1, &(main_data->platform), &(main_data->num_platforms));
	
	main_data->err = clGetDeviceIDs((main_data->platform), CL_DEVICE_TYPE_GPU, 1, &(main_data->device_id), NULL);
	main_data->context = clCreateContext(NULL, 1, &(main_data->device_id), NULL, NULL, &(main_data->err));
	main_data->command_queue = clCreateCommandQueue(main_data->context, (main_data->device_id), 0, &(main_data->err));

	main_data->program = clCreateProgramWithSource(main_data->context, 1, &(main_data->command), NULL, &(main_data->err));
	
	main_data->err = clBuildProgram(main_data->program, 1, &(main_data->device_id), NULL, NULL, NULL);
	main_data->kernel = clCreateKernel(main_data->program, "render", &(main_data->err));
	main_data->memobj = NULL;
	main_data->memLenth = HEIGHT * WIDTH;
	main_data->mem = (cl_int *)main_data->image_data;

	main_data->memobj = clCreateBuffer(main_data->context, CL_MEM_READ_WRITE, main_data->memLenth * sizeof(cl_int), NULL, &(main_data->err));

/* устанавливаем параметр */
	main_data->color = 0x000001;
	main_data->err = clSetKernelArg(main_data->kernel, 0, sizeof(cl_mem), (void *)&(main_data->memobj)); 
	main_data->err = clSetKernelArg(main_data->kernel, 1, sizeof(main_data->x_min), &(main_data->x_min));
	main_data->err = clSetKernelArg(main_data->kernel, 2, sizeof(main_data->x_max), &(main_data->x_max));
	main_data->err = clSetKernelArg(main_data->kernel, 3, sizeof(main_data->y_min), &(main_data->y_min));
	main_data->err = clSetKernelArg(main_data->kernel, 4, sizeof(main_data->y_max), &(main_data->y_max));
	main_data->err = clSetKernelArg(main_data->kernel, 5, sizeof(main_data->max_iter), &(main_data->max_iter));
	
	main_data->global_work_size = WIDTH * HEIGHT;

/* выполнить кернел */
	main_data->err = clEnqueueNDRangeKernel(main_data->command_queue, main_data->kernel, 1, NULL, &(main_data->global_work_size), NULL, 0, NULL, NULL);


/* считать данные из буфера */
	main_data->err = clEnqueueReadBuffer(main_data->command_queue, main_data->memobj, CL_TRUE, 0, main_data->memLenth * sizeof(cl_int), main_data->mem, 0, NULL, NULL);
	
	clFinish(main_data->command_queue);
	mlx_put_image_to_window(main_data->ptr, main_data->win, main_data->image, 0, 0);
	controls(main_data);

	mlx_loop(main_data->ptr);
	return(0);
}

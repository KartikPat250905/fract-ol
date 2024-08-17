/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:23 by karpatel          #+#    #+#             */
/*   Updated: 2024/07/19 14:25:24 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	malloc_failed(void)
{
	perror("Problem with malloc");
	exit(EXIT_FAILURE);
}

void	data_init(t_fractol *fractol)
{
	fractol -> escape_value = 4;
	fractol -> iterations_definition = 100;
	fractol -> shift_x = 0.0;
	fractol -> shift_y = 0.0;
	fractol -> zoom = 1.0;
}

void	events_init(t_fractol *fractol)
{
	mlx_hook(fractol -> mlxwindow, KeyPress,
		KeyPressMask, key_handler, fractol);
	mlx_hook(fractol -> mlxwindow, ButtonPress,
		ButtonPressMask, mouse_handler, fractol);
	mlx_hook(fractol -> mlxwindow, DestroyNotify,
		StructureNotifyMask, close_handler, fractol);
}

void	fractol_init(t_fractol *fractol)
{
	fractol -> mlxconnection = mlx_init();
	if (fractol -> mlxconnection == NULL)
		malloc_failed();
	fractol -> mlxwindow = mlx_new_window(fractol -> mlxconnection,
			WIDTH, HEIGHT, fractol -> name);
	if (fractol -> mlxwindow == NULL)
	{
		mlx_destroy_display(fractol -> mlxconnection);
		free(fractol -> mlxconnection);
		malloc_failed();
	}
	fractol -> img.img_ptr = mlx_new_image(fractol -> mlxconnection,
			WIDTH, HEIGHT);
	if (fractol -> img.img_ptr == NULL)
	{
		mlx_destroy_window(fractol -> mlxconnection, fractol -> mlxwindow);
		mlx_destroy_display(fractol -> mlxconnection);
		free(fractol -> mlxconnection);
		malloc_failed();
	}
	fractol -> img.pixels_ptr = mlx_get_data_addr(fractol -> img.img_ptr,
			&fractol -> img.bpp, &fractol -> img.line_len,
			&fractol -> img.endian);
	events_init(fractol);
	data_init(fractol);
}

int	main(int argc, char *argv[])
{
	t_fractol	fractol;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractol.name = argv[1];
		if (!ft_strncmp(fractol.name, "julia", 5) && (!checkargs(argv[2])
				|| !checkargs(argv[3])))
			errorwithargs();
		if (!ft_strncmp(fractol.name, "julia", 5))
		{
			fractol.julia_x = altodl(argv[2]);
			fractol.julia_y = altodl(argv[3]);
			checkrange(fractol.julia_x, fractol.julia_y);
		}
		fractol_init(&fractol);
		fractol_render(&fractol);
		mlx_loop(fractol.mlxconnection);
	}
	else
	{
		ft_putstr_fd("Usage:\n\tmandelbrot\n\tjulia <real> <i>", 2);
		exit(EXIT_FAILURE);
	}
}

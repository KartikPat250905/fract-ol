/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:32 by karpatel          #+#    #+#             */
/*   Updated: 2024/07/19 14:25:33 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img -> line_len) + (x * (img -> bpp / 8));
	*(unsigned int *)(img -> pixels_ptr + offset) = color;
}

double	scale(double unscaled_num, t_range range)
{
	return ((range.new_max - range.new_min) * (unscaled_num - range.old_min)
		/ (range.old_max - range.old_min) + range.new_min);
}

static void	mandel_julia(t_complex *z, t_complex *c, t_fractol *fractol)
{
	if (!ft_strncmp(fractol -> name, "julia", 5))
	{
		c -> real = fractol -> julia_x;
		c -> imaginary = -1 * fractol -> julia_y;
	}
	else
	{
		c -> real = z -> real;
		c -> imaginary = z -> imaginary;
	}
}

void	handle_pixel(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;
	t_range		ranges[3];

	i = 0;
	range_init(ranges, fractol);
	z.real = (scale(x, ranges[0]) * fractol -> zoom) + fractol -> shift_x;
	z.imaginary = (scale(y, ranges[1]) * fractol -> zoom) + fractol -> shift_y;
	mandel_julia(&z, &c, fractol);
	color = colorhelper(fractol, z, c, ranges[2]);
	my_pixel_put(x, y, &fractol -> img, color);
}

void	fractol_render(t_fractol *fractol)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractol);
		}
	}
	mlx_put_image_to_window(fractol -> mlxconnection,
		fractol -> mlxwindow, fractol -> img.img_ptr, 0, 0);
}

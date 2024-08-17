/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:09 by karpatel          #+#    #+#             */
/*   Updated: 2024/07/19 14:25:14 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractol *fractol)
{
	mlx_destroy_image(fractol -> mlxconnection, fractol -> img.img_ptr);
	mlx_destroy_window(fractol -> mlxconnection, fractol -> mlxwindow);
	mlx_destroy_display(fractol -> mlxconnection);
	free (fractol -> mlxconnection);
	exit(EXIT_SUCCESS);
}

int	mouse_handler(int button, int x, int y, t_fractol *fractol)
{
	(void)x;
	(void)y;
	if (button == Button4)
	{
		fractol -> zoom *= 0.95;
	}
	else if (button == Button5)
	{
		fractol -> zoom *= 1.05;
	}
	fractol_render(fractol);
	return (0);
}

void	range_init(t_range *arr, t_fractol *fractol)
{
	arr[0].old_min = 0;
	arr[0].old_max = WIDTH;
	arr[0].new_min = -2;
	arr[0].new_max = 2;
	arr[1].old_min = 0;
	arr[1].old_max = HEIGHT;
	arr[1].new_min = 2;
	arr[1].new_max = -2;
	arr[2].old_min = 0;
	arr[2].old_max = fractol->iterations_definition;
	arr[2].new_min = BLACK;
	arr[2].new_max = WHITE;
}

int	key_handler(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape)
		close_handler(fractol);
	if (keysym == XK_Left)
		fractol -> shift_x += (0.5 * fractol -> zoom);
	else if (keysym == XK_Right)
		fractol -> shift_x -= (0.5 * fractol -> zoom);
	else if (keysym == XK_Up)
		fractol -> shift_y -= (0.5 * fractol -> zoom);
	else if (keysym == XK_Down)
		fractol -> shift_y += (0.5 * fractol -> zoom);
	else if (keysym == 61)
		fractol -> iterations_definition += 10;
	else if (keysym == XK_minus)
		fractol -> iterations_definition -= 10;
	fractol_render(fractol);
	return (0);
}

void	errorwithargs(void)
{
	ft_putstr_fd("The arguments are not as expected.\n"
		"Please retry with julia real and "
		"imaginary to range of [-2,2]\n ", 2);
	exit(EXIT_FAILURE);
}

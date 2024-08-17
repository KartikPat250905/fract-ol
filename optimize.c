/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:57:50 by karpatel          #+#    #+#             */
/*   Updated: 2024/07/22 13:57:54 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	colorhelper(t_fractol *fractol, t_complex z, t_complex c, t_range range)
{
	int		i;
	double	real_squared;
	double	checkvalue;
	double	imaginery_squared;

	i = 0;
	while (i < fractol->iterations_definition)
	{
		real_squared = z.real * z.real;
		imaginery_squared = z.imaginary * z.imaginary;
		checkvalue = real_squared + imaginery_squared;
		if (checkvalue > fractol->escape_value)
			return (scale(i, range));
		z = sum_complex(square_complex(z, real_squared,
					imaginery_squared), c);
		i++;
	}
	return (PSYCHEDELIC_BLUE);
}

int	ft_isalphabet(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9') ||
			(str[i] == '.' || str[i] == '+' || str[i] == '-')))
			return (1);
		i++;
	}
	return (0);
}

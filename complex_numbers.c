/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:25:02 by karpatel          #+#    #+#             */
/*   Updated: 2024/07/19 14:25:04 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	sum_complex(t_complex num1, t_complex num2)
{
	t_complex	new;

	new.real = num1.real + num2.real;
	new.imaginary = num1.imaginary + num2.imaginary;
	return (new);
}

t_complex	square_complex(t_complex num, double real_squared, double i_square)
{
	t_complex	result;

	result.real = (real_squared) - (i_square);
	result.imaginary = 2 * num.real * num.imaginary;
	return (result);
}

double	altodl(char *s)
{
	long		interger_part;
	double		fractional_part;
	double		pow;
	int			sign;

	fractional_part = 0;
	interger_part = 0;
	sign = +1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -sign;
	while ((*s != '.') && *s)
		interger_part = (interger_part * 10) + (*s++ - 48);
	if (*s == '.')
		s++;
	while (*s)
	{
		pow /= 10;
		fractional_part = fractional_part + (*s++ - 48) * pow;
	}
	return ((interger_part + fractional_part) * sign);
}

int	checkargs(char *str)
{
	int	i;

	i = 0;
	if (ft_isalphabet(str))
		return (0);
	if (*str == '0' && str[1] == '\0')
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == '.' && str[i + 1] != '\0')
		i++;
	else
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void	checkrange(double x, double y)
{
	if (x > 2.0 || x < -2.0)
		errorwithargs();
	if (y > 2.0 || y < -2.0)
		errorwithargs();
}

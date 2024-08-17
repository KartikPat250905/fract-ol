/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:46:48 by karpatel          #+#    #+#             */
/*   Updated: 2024/07/19 14:46:50 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"

# define WIDTH 800
# define HEIGHT 800
# define BLACK       0x000000
# define WHITE       0xFFFFFF
# define RED         0xFF0000
# define GREEN       0x00FF00
# define BLUE        0x0000FF
# define CYAN        0x00FFFF
# define MAGENTA     0xFF00FF
# define YELLOW      0xFFFF00
# define ORANGE      0xFFA500
# define PURPLE      0x800080
# define BROWN       0xA52A2A
# define GRAY        0x808080
# define PSYCHEDELIC_PINK        0xFF69B4
# define PSYCHEDELIC_ORANGE      0xFF4500
# define PSYCHEDELIC_GREEN       0x00FF7F
# define PSYCHEDELIC_PURPLE      0x9400D3
# define PSYCHEDELIC_YELLOW      0xFFD700
# define PSYCHEDELIC_BLUE        0x7B68EE
# define PSYCHEDELIC_RED         0xFF6347
# define PSYCHEDELIC_TURQUOISE   0x40E0D0
# define PSYCHEDELIC_LIME        0x32CD32
# define PSYCHEDELIC_AQUA        0x00FFFF
# define PSYCHEDELIC_MAGENTA     0xFF00FF
# define PSYCHEDELIC_GOLD        0xFFD700

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_range
{
	double	old_min;
	double	old_max;
	double	new_min;
	double	new_max;
}				t_range;

typedef struct s_complex
{
	double	real;
	double	imaginary;
}				t_complex;

typedef struct s_fractol
{
	void	*mlxconnection;
	void	*mlxwindow;
	char	*name;
	t_img	img;
	double	escape_value;
	int		iterations_definition;
	double	shift_x;
	double	shift_y;
	double	julia_x;
	double	julia_y;
	double	zoom;
}				t_fractol;

t_complex	sum_complex(t_complex num1, t_complex num2);
t_complex	square_complex(t_complex num, double real_squared, double i_square);
int			ft_printf(const char *str, ...);
void		handle_pixel(int x, int y, t_fractol *fractol);
double		scale(double unscaled_num, t_range range);
void		fractol_render(t_fractol *fractol);
int			key_handler(int keysym, t_fractol *fractol);
int			close_handler(t_fractol *fractol);
int			mouse_handler(int button, int x, int y, t_fractol *fractol);
double		altodl(char *s);
void		errorwithargs(void);
int			checkargs(char *str);
void		checkrange(double x, double y);
int			colorhelper(t_fractol *fractol, t_complex z,
				t_complex c, t_range range);
int			ft_isalphabet(char *str);
void		range_init(t_range *arr, t_fractol *fractol);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:01:24 by rburton           #+#    #+#             */
/*   Updated: 2021/01/30 02:42:13 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_TEST_H
# define MLX_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct		s_color
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct  s_vars {
    void		*mlx; //pointer for mlx instance
    void		*win; //pointer for mlx window instance
}               t_vars;

typedef struct 		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pix;
	int				line_lngth;
	int				endian;
}					t_data;

typedef struct		s_rsltn
{
	unsigned int	x;
	unsigned int	y;
}					t_rsltn;

typedef struct 		s_crcl
{
	int				start_x;
	int				start_y;
	float				r;
	int				color;
}					t_crcl;

typedef struct  s_whole {
    unsigned int    **pxl_arr;
    t_rsltn         rsltn;
    t_vars          vrs;
    t_data          dt;
    int             lim;
}               t_whole;

#endif
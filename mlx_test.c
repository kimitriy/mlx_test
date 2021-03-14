/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:25:56 by rburton           #+#    #+#             */
/*   Updated: 2021/03/14 20:30:33 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_test.h"

//GRAPHICS////////////////////////////////////////////////////////////////

void	color_make(t_color *color, unsigned int r, unsigned int g, unsigned int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}

unsigned long cnvrse2trgb(t_color *trgb)
{   
	return (((trgb->t & 0xff) << 24) + ((trgb->r & 0xff) << 16) + ((trgb->g & 0xff) << 8) + (trgb->b & 0xff));
}

unsigned int	**make_pxl_arr(t_rsltn *xy)
{
	unsigned int 	x;
	unsigned int	y;
	unsigned int	**pxl_arr;
	t_color			grey;

	y = 0;
	// printf("x:%d\n", xy->x);
	// printf("y:%d\n", xy->y);
	if (!(pxl_arr = (unsigned int**)malloc((xy->y) * sizeof(unsigned int*))))
		return (NULL);
	while (y < xy->y)
	{
		if (!(pxl_arr[y] = (unsigned int*)malloc((xy->x) * sizeof(unsigned int))))
			return (NULL);
		y++;
	}
	y = 0;
	x = 0;
	color_make(&grey, 0, 0, 0);
	while (y < xy->y)
	{
		while (x < xy->x)
		{
			pxl_arr[y][x] = (unsigned int)cnvrse2trgb(&grey);
			x++;
		}
		x = 0;
		y++;
	}
	return (pxl_arr);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lngth + x * (data->bits_per_pix / 8));
	*(unsigned int*)dst = color;
}

void	make_new_crcl(t_crcl *ncrcl)
{
	ncrcl->start_x = 500;
	ncrcl->start_y = 500;
	ncrcl->r = 300;
	ncrcl->color = 0x0000FF00;
}

//to Cartesian
//x_cart = x - resolution_width / 2
//y_cart = resolution_height / 2 - y
//from Cartesian
//x = resolution_width / 2 + x_cart
//y = resolution_height / 2 - y_cart

void	draw_crcl(t_whole *the_w)
{
	t_crcl			ncrcl;
	float 			x_cart;
	float 			y_cart;
	float			pi;
	unsigned int	x;
	unsigned int	y;
	float			angle;
	
	make_new_crcl(&ncrcl);
	
	pi = 3.141593;
	angle = 0;
	x_cart = 0;
	y_cart = 0;
	while (angle <= the_w->lim)
	{
		x_cart = ncrcl.r * cosf(angle * pi / 180);
		y_cart = ncrcl.r * sinf(angle * pi / 180);
		x = ncrcl.start_x + (int)x_cart;
		y = ncrcl.start_y - (int)y_cart;
		if (x >= 0 && x < the_w->rsltn.x && y >= 0 && y < the_w->rsltn.y)
			the_w->pxl_arr[y][x] = ncrcl.color;
		angle += 0.1;
	}
}

void	draw_from_arr(t_whole *the_w)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 0;
	while (y < the_w->rsltn.y)
	{
		while (x < the_w->rsltn.x)
		{
			my_mlx_pixel_put(&the_w->dt, x, y, the_w->pxl_arr[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}

void	img_node(t_whole *the_w)
{	
	draw_crcl(the_w);
	if (the_w->pxl_arr != NULL)
		draw_from_arr(the_w);
	mlx_put_image_to_window(the_w->vrs.mlx, the_w->vrs.win, the_w->dt.img, 0, 0);
	mlx_destroy_image(the_w->vrs.mlx, the_w->dt.img);
	the_w->dt.img = mlx_new_image(the_w->vrs.mlx, the_w->rsltn.x, the_w->rsltn.y);
	the_w->dt.addr = mlx_get_data_addr(the_w->dt.img, &the_w->dt.bits_per_pix, &the_w->dt.line_lngth, &the_w->dt.endian);
}

//HOOKS////////////////////////////////////////////////////////////////

void	ft_putnbr(int n)
{
	char	ch;
	
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(n * (-1));
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{	
		ch = n + '0';
		write(1, &ch, 1);
	}
}

int		key_hook(int keycode, t_whole *the_w)
{
	// int  scr_w;
	// int  scr_h;

	ft_putnbr(keycode);
	write(1, "\n", 1);
	if (keycode == 13)
	{
		the_w->lim += 15;
		img_node(the_w);
	}
	// mlx_get_screen_size(the_w->vrs.mlx, &scr_w, &scr_h);
	// printf("scr_w:%d, scr_h:%d\n", scr_w, scr_h);
	return (0);
}

int		close_mlx_win(int keycode, t_vars *vrs)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vrs->mlx, vrs->win);
		exit (0);
	}
	return (0);
}

int		stop_ex(t_vars *vrs)
{
	mlx_destroy_window(vrs->mlx, vrs->win);
	exit (0);
	return (0);
}

void	func(t_whole *the_w)
{
    the_w->vrs.mlx = mlx_init();
	the_w->vrs.win = mlx_new_window(the_w->vrs.mlx, the_w->rsltn.x, the_w->rsltn.y, "mlx_window"); //initialises new window
	the_w->dt.img = mlx_new_image(the_w->vrs.mlx, the_w->rsltn.x, the_w->rsltn.y);
	the_w->dt.addr = mlx_get_data_addr(the_w->dt.img, &the_w->dt.bits_per_pix, &the_w->dt.line_lngth, &the_w->dt.endian);
	mlx_key_hook(the_w->vrs.win, key_hook, the_w);
    mlx_hook(the_w->vrs.win, 2, 1L<<0, close_mlx_win, &the_w->vrs);
	mlx_hook(the_w->vrs.win, 17, 1L << 2, stop_ex, &the_w->vrs);
	
	img_node(the_w);
	
	mlx_loop(the_w->vrs.mlx); //holds the window opened
}

//MAIN/////////////////////////////////////////////////////////////////////

int		main(int argc, char **argv)
{
	t_whole		the_w; //where hook changes something

	(void)argc;
	(void)argv;
	// if (argv[1][0] == 's')
		

	the_w.rsltn.x = 1000;
	the_w.rsltn.y = 1000;

	the_w.pxl_arr = make_pxl_arr(&the_w.rsltn);

	the_w.lim = 0;
	
	int  scr_w;
	int  scr_h;
	mlx_get_screen_size(the_w.vrs.mlx, &scr_w, &scr_h);
	printf("s_w: %d, s_h: %d\n", scr_w, scr_h);

	func(&the_w);

	return (0);
}
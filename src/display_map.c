/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:43:47 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/29 15:10:35 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "so_long.h"

t_data	create_image(void *mlx, char *path)
{
	t_data	image;

	image.img = mlx_xpm_file_to_image(mlx, path, &image.width, &image.heigh);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, \
	&image.line_length, &image.endian);
	return (image);
}

void	*create_window(void *mlx, char **map)
{
	void	*mlx_win;
	int		h;

	h = 0;
	while (map[h])
		h++;
	mlx_win = mlx_new_window(mlx, ft_strlen(map[0]) * 50, h * 50, "so_long");
	return (mlx_win);
}

t_vars	display_basics(char **map, t_vars v, int i)
{
	int		y;
	t_data	wall;
	t_data	coll;

	coll = create_image(v.mlx, "./img/collectible.xpm");
	wall = create_image(v.mlx, "./img/wall.xpm");
	v.grass = create_image(v.mlx, "./img/grass.xpm");
	while (map[i / 50])
	{
		y = 0;
		while (map[i / 50][y / 50])
		{
			if (map[i / 50][y / 50] == '1')
				mlx_put_image_to_window(v.mlx, v.win, wall.img, y, i);
			if (map[i / 50][y / 50] == '0' || map[i / 50][y / 50] == 'E')
				mlx_put_image_to_window(v.mlx, v.win, v.grass.img, y, i);
			if (map[i / 50][y / 50] == 'C')
				mlx_put_image_to_window(v.mlx, v.win, coll.img, y, i);
			y += 50;
		}
		i += 50;
	}
	mlx_destroy_image(v.mlx, coll.img);
	mlx_destroy_image(v.mlx, wall.img);
	return (v);
}

t_vars	display_map(char **map)
{
	t_vars		var;

	var.mlx = mlx_init();
	var.win = create_window(var.mlx, map);
	var = display_basics(map, var, 0);
	var.exit = create_image(var.mlx, "./img/exit.xpm");
	var.map = map;
	return (var);
}

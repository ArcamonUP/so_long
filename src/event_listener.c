/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:54:34 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/29 18:39:02 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>
#include "libft.h"

int	check_possible_move(t_vars *var, int num)
{
	if (num == 1)
		return ((*var).map[var->pos_player.x - 1][var->pos_player.y] != '1');
	if (num == 2)
		return ((*var).map[var->pos_player.x][var->pos_player.y - 1] != '1');
	if (num == 3)
		return ((*var).map[var->pos_player.x + 1][var->pos_player.y] != '1');
	if (num == 4)
		return ((*var).map[var->pos_player.x][var->pos_player.y + 1] != '1');
	return (1);
}

t_vars	*move(t_vars *var, int num)
{
	if (!check_possible_move(var, num))
		return (var);
	mlx_put_image_to_window((*var).mlx, (*var).win, (*var).grass.img, \
	50 * (*var).pos_player.y, 50 * (*var).pos_player.x);
	if (num == 1)
		(*var).pos_player.x -= 1;
	if (num == 2)
		(*var).pos_player.y -= 1;
	if (num == 3)
		(*var).pos_player.x += 1;
	if (num == 4)
		(*var).pos_player.y += 1;
	mlx_put_image_to_window((*var).mlx, (*var).win, (*var).player.img, \
	50 * (*var).pos_player.y, 50 * (*var).pos_player.x);
	if ((*var).map[var->pos_player.x][var->pos_player.y] != 'E')
		(*var).map[var->pos_player.x][var->pos_player.y] = '0';
	var->count++;
	return (ft_printf("Nb of moves : %d\r", var->count), var);
}

int	end_game(t_vars *v)
{
	mlx_destroy_image(v->mlx, v->grass.img);
	mlx_destroy_image(v->mlx, v->player.img);
	mlx_destroy_image(v->mlx, v->exit.img);
	mlx_destroy_window(v->mlx, v->win);
	mlx_loop_end(v->mlx);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	free_map(v->map);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *var)
{
	t_position	temp;

	if (keycode == KEY_ESC)
		return (end_game(var));
	else if (keycode == KEY_LEFT)
		var = move(var, 1);
	else if (keycode == KEY_UP)
		var = move(var, 2);
	else if (keycode == KEY_RIGHT)
		var = move(var, 3);
	else if (keycode == KEY_DOWN)
		var = move(var, 4);
	if (get_pos(var->map, 'C').x == -1 && \
	(*var).map[var->pos_player.x][var->pos_player.y] == 'E')
		return (ft_printf("\n"), end_game(var));
	if (get_pos(var->map, 'C').x == -1 && var->num == 0)
	{
		temp = get_pos(var->map, 'E');
		mlx_put_image_to_window(var->mlx, var->win, var->exit.img, \
		50 * temp.y, 50 * temp.x);
		var->num = 1;
	}
	return (0);
}

void	event_listener(char **map, t_vars var)
{
	var.player = create_image(var.mlx, "./img/tondeuse.xpm");
	var.pos_player = get_pos(map, 'P');
	mlx_put_image_to_window(var.mlx, var.win, var.player.img, \
	50 * var.pos_player.y, 50 * var.pos_player.x);
	mlx_key_hook(var.win, key_hook, &var);
	mlx_hook(var.win, 17, 0, end_game, &var);
	mlx_loop(var.mlx);
}

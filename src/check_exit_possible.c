/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_possible.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:04:40 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/17 16:12:28 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"
#include <stdlib.h>
#include "libft.h"

int	est_valide(int x, int y, char **map, int **visited)
{
	if (x < 0 || y < 0 || map[x] == NULL || map[x][y] == '\0' \
	|| map[x][y] == '1' || visited[x][y])
		return (0);
	return (1);
}

static const int	g_directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int	explore_chemin(char **map, int **visited, t_position pos, t_position exit)
{
	int			i;
	t_position	n;

	if (pos.x == exit.x && pos.y == exit.y)
		return (1);
	visited[pos.x][pos.y] = 1;
	i = 0;
	while (i < 4)
	{
		n.x = pos.x + g_directions[i][0];
		n.y = pos.y + g_directions[i][1];
		if (est_valide(n.x, n.y, map, visited))
			if (explore_chemin(map, visited, n, exit))
				return (1);
		i++;
	}
	return (0);
}

t_position	get_pos(char **map, char c)
{
	t_position	pos;
	int			i;
	int			y;

	i = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == c)
			{
				pos.x = i;
				pos.y = y;
				return (pos);
			}
			y++;
		}
		i++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

int	check_exit_possible(char **map, int nb_lines)
{
	int			**visited;
	int			i;
	t_position	start;
	t_position	exit;
	t_position	*collectibles;

	visited = ft_calloc(nb_lines + 1, sizeof(int *));
	if (!visited)
		return (0);
	i = 0;
	while (map[i])
	{
		visited[i] = ft_calloc(ft_strlen(map[i]), sizeof(int));
		if (!visited[i])
			return (0);
		i++;
	}
	start = get_pos(map, 'P');
	exit = get_pos(map, 'E');
	collectibles = get_collectibles(map, 0);
	if (!explore_chemin(map, visited, start, exit))
		return (free(collectibles), free_tab_int(visited), 0);
	if (!check_coll(map, visited, start, collectibles))
		return (free(collectibles), free_tab_int(visited), 0);
	return (free(collectibles), free_tab_int(visited), 1);
}

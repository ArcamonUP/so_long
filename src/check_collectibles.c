/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collectibles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:43:30 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/16 12:01:08 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <stdlib.h>

int	get_count_collectibles(char **map)
{
	int	count;
	int	i;
	int	y;

	count = 0;
	i = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == 'C')
				count++;
			y++;
		}
		i++;
	}
	return (count);
}

t_position	*get_collectibles(char **map, int i)
{
	t_position	*collectibles;
	int			y;
	int			count;

	collectibles = ft_calloc(sizeof(t_position), get_count_collectibles(map));
	if (!collectibles)
		return (NULL);
	i = 0;
	count = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == 'C')
			{
				collectibles[count].x = i;
				collectibles[count].y = y;
				count++;
			}
			y++;
		}
		i++;
	}
	return (collectibles);
}

int	**reset_tab(char **map, int **tab)
{
	int	i;
	int	y;

	i = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			tab[i][y] = 0;
			y++;
		}
		i++;
	}
	return (tab);
}

int	check_coll(char **map, int	**visited, t_position start, t_position *coll)
{
	int	count;
	int	i;

	count = get_count_collectibles(map);
	i = 0;
	while (i < count)
	{
		visited = reset_tab(map, visited);
		if (!explore_chemin(map, visited, start, coll[i]))
			return (0);
		i++;
	}
	return (1);
}

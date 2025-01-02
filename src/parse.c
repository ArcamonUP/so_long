/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:50:05 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/29 16:03:42 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <stdio.h>
#include <fcntl.h>

char	**init(char *filename, int nb_lines)
{
	char	*temp;
	char	**map;
	int		count;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (nb_lines + 1));
	if (fd == -1 || !map)
		return (free_map(map), NULL);
	count = 0;
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		map[count] = realloc_without_nl(temp);
		count++;
		temp = get_next_line(fd);
	}
	map[count] = NULL;
	return (close(fd), map);
}

int	check_char_exists(char **map, int c_count, int e_count, int p_count)
{
	int	i;
	int	y;

	i = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == 'C')
				c_count++;
			else if (map[i][y] == 'E')
				e_count++;
			else if (map[i][y] == 'P')
				p_count++;
			else if (map[i][y] != '0' && map[i][y] != '1')
				return (0);
			y++;
		}
		i++;
	}
	if (c_count < 1 || e_count != 1 || p_count != 1)
		return (0);
	return (1);
}

int	is_a_rectangle(char **map)
{
	int	len;
	int	i;
	int	y;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
			y++;
		if (y != len)
			return (0);
		i++;
	}
	return (1);
}

int	check_map_valid(char **map)
{
	int	i;
	int	y;

	if (!check_line(map[0], '1'))
		return (0);
	i = 0;
	while (map[i + 1])
	{
		y = 0;
		if (map[i][0] != '1')
			return (0);
		while (map[i][y])
		{
			if (!map[i][y + 1] && map[i][y] != '1')
				return (0);
			y++;
		}
		i++;
	}
	if (!check_line(map[i], '1'))
		return (0);
	return (is_a_rectangle(map));
}

char	**parse(char *filename, int nb_lines)
{
	char	**map;

	map = init(filename, nb_lines);
	if (!map)
		return (NULL);
	if (!check_char_exists(map, 0, 0, 0))
	{
		write(2, "Error\nMap must contain 1 exit, item and start pos.\n", 51);
		return (free_map(map), NULL);
	}
	if (!check_map_valid(map))
	{
		write(2, "Error\nMap must be a square surrounded by walls.\n", 48);
		return (free_map(map), NULL);
	}
	if (!check_exit_possible(map, nb_lines))
	{
		write(2, "Error\nMap must contain a path to the exit", 41);
		write(2, " and all collectibles must be accesible.\n", 41);
		return (free_map(map), NULL);
	}
	if (!check_map_size(map, nb_lines))
		return (free_map(map), NULL);
	return (map);
}

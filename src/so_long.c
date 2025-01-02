/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:06:54 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/29 16:45:42 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>
#include <fcntl.h>

int	get_nb_lines(char *filename)
{
	int		result;
	int		fd;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nWrong path: Unable to open the file.\n", 43);
		return (0);
	}
	result = 0;
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		result++;
		free(temp);
		temp = get_next_line(fd);
	}
	(free(temp), close(fd));
	if (result == 0)
	{
		write(2, "Error\nThe file cannot be read. ", 31);
		write(2, "Either the file is empty, or it's not a file.\n", 46);
	}
	return (result);
}

int	main(int ac, char **av)
{
	int		nb_lines;
	int		i;
	char	**map;
	t_vars	var;

	if (ac != 2)
		return (0);
	i = ft_strlen(av[1]) - 4;
	if (i < 0 || ft_strncmp(av[1] + i, ".ber", 4) != 0)
	{
		write(2, "Error\nMap file must end with .ber\n", 34);
		return (0);
	}
	nb_lines = get_nb_lines(av[1]);
	if (nb_lines == 0)
		return (0);
	map = parse(av[1], nb_lines);
	if (!map)
		return (0);
	var = display_map(map);
	var.count = 0;
	var.num = 0;
	event_listener(map, var);
}

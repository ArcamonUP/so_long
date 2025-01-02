/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:08:45 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/29 15:21:27 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <mlx.h>

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_tab_int(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*realloc_without_nl(char *str)
{
	char	*result;
	int		i;

	i = 0;
	if (!ft_strchr(str, '\n'))
		return (str);
	result = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		result[i] = str[i];
		if (str[i] == '\n')
			result[i] = '\0';
		i++;
	}
	free(str);
	return (result);
}

int	check_line(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	check_map_size(char **map, int nb_lines)
{
	int		width;
	int		height;
	void	*mlx;

	mlx = mlx_init();
	mlx_get_screen_size(mlx, &width, &height);
	if (width - 50 > (int)(ft_strlen(map[0]) * 50) && \
	height - 50 > nb_lines * 50)
		return (1);
	ft_printf("Error\n");
	ft_printf("Map is much too large, be reasonable and enter");
	ft_printf(" a smaller map.\n");
	return (0);
}

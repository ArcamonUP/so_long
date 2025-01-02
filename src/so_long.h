/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:58:26 by kbaridon          #+#    #+#             */
/*   Updated: 2024/12/29 15:15:19 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define KEY_LEFT 119
# define KEY_RIGHT 115
# define KEY_UP 97
# define KEY_DOWN 100
# define KEY_ESC 65307

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		width;
	int		heigh;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			grass;
	t_data			player;
	t_data			exit;
	t_position		pos_player;
	char			**map;
	unsigned int	count;
	unsigned int	num;
}	t_vars;

void		free_map(char **map);
void		free_tab_int(int **tab);
char		**parse(char *filename, int nb_lines);
int			check_exit_possible(char **map, int nb_lines);
int			check_line(char *line, char c);
char		*realloc_without_nl(char *str);
t_vars		display_map(char **map);
int			check_coll(char **map, int	**visited, \
t_position start, t_position *coll);
int			explore_chemin(char **map, int **visited, \
t_position pos, t_position exit);
t_position	*get_collectibles(char **map, int i);
t_data		create_image(void *mlx, char *path);
t_position	get_pos(char **map, char c);
void		event_listener(char **map, t_vars var);
int			check_map_size(char **map, int nb_lines);

#endif
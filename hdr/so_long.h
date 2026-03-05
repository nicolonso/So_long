/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:08:15 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/05 23:03:20 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// Libraries

# include "../Lib/hdr/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

// Space in bytes for my images
# define TILE 64

// Linux Key codes (X11)

# define KEY_ESC 	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100

// Structures 

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		c_count;
	int		p_count;
	int		e_count;
	int		px;
	int		py;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**grid;
	int		width;
	int		heigth;
	int		px;
	int		py;
	int		collectibles;
	int		img_w;
	int		img_h;
	int		moves;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collect;
	void	*img_exit;
}	t_game;

//Initialize structures

void	ft_init_map(t_map *m);
void	ft_game_init(t_game *g, t_map *m, char **grid);
// Parsing

//  Parsing main Functions

int		ft_parsing(char **av, t_map *m);
int		ft_read_map_gnl(int fd, t_map *m);
int		ft_valid_and_count_row(t_map *m, char *row, int y);
char	**ft_append_row(char **grid, int height, char *row);
int		ft_check_walls(t_map *m);
int		ft_check_reachable(t_map *m);
int		ft_check_reachable_collectibles(t_map *m);
void	ft_flood_fill(char **map, int x, int y, t_map *m);
void	ft_flood_fill_check(char **map, int x, int y, t_map *m);

// Parsing Helper Functions

int		ft_line_len_no_nl(const char *line);
char	**ft_copy_grid(char **map);
int		ft_len_map_square(char **map);
int		ft_is_ber(char *file);

// Helper Functions

void	ft_free(char **ptr, int row);
char	*ft_dup_no_nl(char *line);
void	ft_free_grid(char **ptr);
// Architecture 

void	ft_find_player(t_game *g);
void	ft_put_image(t_game *g, void *img, int x, int y);
int		ft_load_textures(t_game *g);
void	ft_render_map(t_game *g);
void	*ft_load(t_game *g, char *path);
int		ft_loop_render(void *param);

// Movements of player

int		ft_handle_key(int keycode, void *param);
int		ft_handle_close(void *param);
void	ft_move_it(t_game *g, int nx, int ny);

#endif
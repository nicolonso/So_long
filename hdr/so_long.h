/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:08:15 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/01 23:30:15 by nalfonso         ###   ########.fr       */
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

// Structures 

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     c_count;
    int     p_count;
    int     e_count;
    int     px;
    int     py;
}   t_map;

//Initialize structures

void	ft_init_map(t_map *m);

// Parsing

//  Parsing main Functions

int		ft_read_map_gnl(int fd, t_map *m);
int		ft_valid_and_count_row(t_map *m, char *row, int y);
char	**ft_append_row(char **grid, int height, char *row);
int 	ft_check_walls(t_map *m);
void	ft_flood_fill(char **map, int x, int y, int w, int h);
int 	ft_check_reachable(t_map *m);

// Parsing Helper Functions

int		ft_line_len_no_nl(const char *line);
char 	**ft_copy_grid(char **map);
int 	ft_len_map_square(char **map);

// Helper Functions

void 	ft_free(char **ptr, int row);
char 	*ft_dup_no_nl(char *line);

#endif
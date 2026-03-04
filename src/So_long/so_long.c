/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:07:45 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/04 23:20:46 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

int main(int ac, char **av)
{
    int   fd;
    t_map m;
	t_game g;

	// Parsing 
    if (ac != 2)
        return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 34), 1);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);

	//Until this line every time that the map is not correct i need to free my struct.
    if (ft_read_map_gnl(fd, &m))
        return (write(2, "Error\nInvalid map\n", 18), close(fd), 1);
    close(fd);
    if (ft_check_walls(&m))
        return (write(2, "Error\nMap not closed by walls\n", 30), 1);
	else if (ft_check_reachable(&m))
	{
		ft_free_grid(m.grid);
		return (write(2, "Error\nMap is not reacheable\n", 29), 1);
	}
	else if (ft_check_reachable_collectibles(&m))
	{
		ft_free_grid(m.grid);
		return (write(2, "Error\nMap is not reacheable\n", 29), 1);
	}
	// Graphic 

	//After this I need to initializes the free in t_map(incluided in the funtion that we are goin put all parsin after init) 
	ft_game_init(&g, &m, m.grid, m.width, m.height);
	g.mlx = mlx_init();
	if (!g.mlx)
		return (write(2, "Error\nmlx_init failed\n", 22), 1);
	g.win = mlx_new_window(g.mlx, g.heigth * TILE ,g.width * TILE, "so_long");
	if (!g.win)
		return (write(2, "Error\nmlx_new_window failed\n", 28), 1);
	mlx_loop_hook(&g.mlx, loop_render, &g);
	if (ft_load_textures(&g))
		return (1);
	ft_render_map(&g);
	// // 4) hooks
	mlx_hook(g.win, 2, 1L << 0, ft_handle_key, &g);   // KeyPress
	mlx_hook(g.win, 17, 0, ft_handle_close, &g);      // DestroyNotify (X button)
	mlx_loop(g.mlx);	
	return 0;
}


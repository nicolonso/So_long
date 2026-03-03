/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:07:45 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/03 23:08:55 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../hdr/so_long.h"

/* static void ft_print_map(t_game *g)
{
	int y = 0;
    int x;

    while (y < g->heigth)
    {
        x = 0;
        while (x < g->width)
        {
            write(1, &g->grid[y][x], 1);
            x++;
        }
        write(1, "\n", 1);
        y++;
    }
} */

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

    if (ft_read_map_gnl(fd, &m))
        return (write(2, "Error\nInvalid map\n", 18), close(fd), 1);

    close(fd);
	ft_printf("Values After check with parsing: w=%d h=%d\n", m.width, m.height);
    if (ft_check_walls(&m))
        return (write(2, "Error\nMap not closed by walls\n", 30), 1);
	
	else if (ft_check_reachable(&m))
		return (write(2, "Error\nMap is not reacheable\n", 29), 1);


	// Graphic 

	ft_game_init(&g, m.grid, m.width, m.height);
	ft_printf("Game init values: w=%d h=%d\n", g.width, g.heigth);
	g.mlx = mlx_init();
	if (!g.mlx)
		return (write(2, "Error\nmlx_init failed\n", 22), 1);
	
	// Option for the value of my window 
	/* while (m.width * tile > 4480 || m.height * tile > 1080)
    tile /= 2;
	if (tile < 16)
    tile = 16;
	win_w = m.width * tile;
	win_h = m.height * tile; */
	g.win = mlx_new_window(g.mlx, g.heigth * TILE ,g.width * TILE, "so_long");
	if (!g.win)
		return (write(2, "Error\nmlx_new_window failed\n", 28), 1);
	if (ft_load_textures(&g))
		return (1);
	ft_render_map(&g);

	// // 4) hooks
	mlx_hook(g.win, 2, 1L << 0, ft_handle_key, &g);   // KeyPress
	mlx_hook(g.win, 17, 0, ft_handle_close, &g);      // DestroyNotify (X button)

	mlx_loop(g.mlx);
	
	return 0;
}


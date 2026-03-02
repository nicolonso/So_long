/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:07:45 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/02 23:38:04 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../hdr/so_long.h"

int main(int ac, char **av)
{
    int   fd;
    t_map m;
	t_game g;
	char cwd[1024];

    if (ac != 2)
        return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 34), 1);
	
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);

    if (ft_read_map_gnl(fd, &m))
        return (write(2, "Error\nInvalid map\n", 18), close(fd), 1);

    close(fd);

    if (ft_check_walls(&m))
        return (write(2, "Error\nMap not closed by walls\n", 30), 1);
	
	else if (ft_check_reachable(&m))
		return (write(2, "Error\nMap is not reacheable\n", 29), 1);

	ft_printf("PARSE: width=%d height=%d px=%d py=%d\n",
    m.width, m.height, m.px, m.py);
	
	//mlx_init();
	//mlx_new_window();
	getcwd(cwd, sizeof(cwd));
	ft_printf("CWD = %s\n", cwd);

    ft_game_init(&g, m.grid, m.width, m.height);

	g.mlx = mlx_init();
	if (!g.mlx)
		return (write(2, "Error\nmlx_init failed\n", 22), 1);
	ft_printf("Test\n");
	g.win = mlx_new_window(g.mlx, g.width * TILE, g.heigth * TILE, "so_long"); /// Im no t passing the info to my game struct so it stuck in process
	if (!g.win)
		return (write(2, "Error\nmlx_new_window failed\n", 28), 1);
	ft_printf("WIN: width=%d height=%d\n", g.width * TILE, g.heigth * TILE);
	// 3) textures + initial render
	ft_printf("Test 2\n");
	if (ft_load_textures(&g)) // NOw everything is fine until here 
		return (1);
	ft_printf("Test 3\n");	
	ft_render_map(&g);

	// 4) hooks
	mlx_hook(g.win, 2, 1L << 0, ft_handle_key, &g);   // KeyPress
	mlx_hook(g.win, 17, 0, ft_handle_close, &g);      // DestroyNotify (X button)

	mlx_loop(g.mlx);
	
	return 0;
}


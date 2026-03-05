/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:07:45 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/05 23:19:43 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_map	m;
	t_game	g;

	if (ac != 2)
		return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 34), 1);
	else if (!ft_is_ber(av[1]))
		return (write(2, "Error\nMap must be a .ber file\n", 30), 1);
	else if (ft_parsing(av, &m))
		return (1);
	ft_game_init(&g, &m, m.grid);
	g.mlx = mlx_init();
	if (!g.mlx)
		return (write(2, "Error\nmlx_init failed\n", 22), 1);
	g.win = mlx_new_window(g.mlx, g.width * TILE, g.heigth * TILE, "so_long");
	if (!g.win)
		return (write(2, "Error\nmlx_new_window failed\n", 28), 1);
	mlx_loop_hook(&g.mlx, ft_loop_render, &g);
	if (ft_load_textures(&g))
		return (1);
	ft_render_map(&g);
	mlx_hook(g.win, 2, 1L << 0, ft_handle_key, &g);
	mlx_hook(g.win, 17, 0, ft_handle_close, &g);
	mlx_loop(g.mlx);
	return (0);
}

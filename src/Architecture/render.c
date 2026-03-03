/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:10:19 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/03 23:16:30 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

void ft_put_image(t_game *g, void *img, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, img, x * TILE, y * TILE);
}

void ft_render_map(t_game *g)
{
	int x;
	int y;
	char t;

	if (!g || !g->grid || g->width <= 0 || g->heigth <= 0)
    	return;
	y = 0;
	while (y < g->heigth)
	{
		x = 0;
		while (x < g->width)
		{
			t = g->grid[y][x];
			ft_put_image(g, g->img_floor, x, y);
			if (t == '1')
				ft_put_image(g, g->img_wall, x, y);
			if (t == 'C')
				ft_put_image(g, g->img_collect, x, y);
			if (t == 'P')
				ft_put_image(g, g->img_player, x, y);
			if (t == 'E')
				ft_put_image(g, g->img_exit, x, y);
			x++;
		}
		y++;
	}
}

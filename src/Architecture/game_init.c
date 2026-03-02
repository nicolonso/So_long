/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:11:51 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/02 19:33:21 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

void ft_find_player(t_game *g)
{
	int x;
	int y;
	
	y = 0;
	while (g->grid[y])
	{
		x = 0;
		while (g->grid[y][x])
		{
			if (g->grid[y][x] == 'P')
			{
				g->px = x;
				g->py = y;
				return ;
			}
			x++;
		}
		y++;
	}
	g->px = -1;
	g->py = -1;
}

void	ft_game_init(t_game *g, char **grid, int w, int h)
{
	g->mlx = NULL;
	g->win = NULL;
	g->grid = grid;
	g->width = w;
	g->heigth = h;
	g->img_player = NULL;
	g->img_collect = NULL;
	g->img_floor = NULL;
	g->img_exit = NULL;
	g->img_wall = NULL;
	g->collectibles = 0;
	g->moves = 0;
	g->img_w = TILE;
	g->img_h = TILE;
	ft_find_player(g);
}

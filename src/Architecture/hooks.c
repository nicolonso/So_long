/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:12:49 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/02 23:18:10 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

int ft_handle_close(void *param)
{
	t_game *g;

	// TODO: destroy images, free map, etc.
	g = (t_game *)param;
	mlx_destroy_window(g->mlx, g->win);
	exit (0);
	return (0);
}

void ft_move_it(t_game *g, int nx, int ny)
{
	if (nx < 0 || ny < 0 || nx >= g->width || ny >= g->heigth)
		return ;
	if (g->grid[ny][nx] == '1')
		return ;
	g->grid[g->py][g->px] = '0';
	g->grid[ny][nx] = 'P';
	g->px = nx;
	g->py = ny;
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	ft_render_map(g);
}

int ft_handle_key(int keycode, void *param)
{
	t_game *g;
	
	g = (t_game *)param;
	if (keycode == KEY_ESC)
		ft_handle_close(g);
	else if (keycode == KEY_W)
		ft_move_it(g, g->px, g->py - 1);
	else if (keycode == KEY_S)
		ft_move_it(g, g->px, g->py + 1);
	else if (keycode == KEY_A)
		ft_move_it(g, g->px - 1, g->py);
	else if (keycode == KEY_D)
		ft_move_it(g, g->px + 1, g->py);
	return (0);
}

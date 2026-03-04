/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:12:49 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/04 23:03:55 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"


void	ft_free_grid(char **ptr)
{
	int	i;
	int len;

	i = -1;
	len = ft_len_map_square(ptr);
	while (++i < len)
		free(ptr[i]);
	free(ptr);
}

void	ft_destroy_game(t_game *g)
{
	if (!g)
		return;
	if (g->grid)
		ft_free_grid(g->grid);
	if (g->img_wall) mlx_destroy_image(g->mlx, g->img_wall);
	if (g->img_floor) mlx_destroy_image(g->mlx, g->img_floor);
	if (g->img_player) mlx_destroy_image(g->mlx, g->img_player);
	if (g->img_collect) mlx_destroy_image(g->mlx, g->img_collect);
	if (g->img_exit) mlx_destroy_image(g->mlx, g->img_exit);
	if (g->win) mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

int	ft_handle_close(void *param)
{
	t_game *g = (t_game *)param;
	ft_destroy_game(g);
	exit(0);
	return (0);
}
/* int ft_handle_close(void *param)
{
	t_game *g;

	// TODO: destroy images, free map, etc.
	g = (t_game *)param;
	mlx_destroy_window(g->mlx, g->win);
	exit (0);
	return (0);
} */

/* void ft_move_it(t_game *g, int nx, int ny)
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
} */

void ft_move_it(t_game *g, int nx, int ny)
{
    if (nx < 0 || ny < 0 || nx >= g->width || ny >= g->heigth)
        return ;
    if (g->grid[ny][nx] == '1')
        return ;
    if (g->grid[ny][nx] == 'C')
        g->collectibles--;
    if (g->grid[ny][nx] == 'E')
    {
        if (g->collectibles == 0) // I need to initializiace my collectibles
        {
            ft_printf("You win in %d moves!\n", g->moves + 1);
            ft_handle_close(g);
        }
        return ;
    }
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

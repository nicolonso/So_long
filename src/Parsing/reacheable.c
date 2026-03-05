/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reacheable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 23:31:18 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/05 21:18:35 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

void	ft_init_map(t_map *m)
{
	m->grid = NULL;
	m->width = -1;
	m->height = 0;
	m->c_count = 0;
	m->p_count = 0;
	m->e_count = 0;
	m->px = -1;
	m->py = -1;
}

void	ft_flood_fill(char **map, int x, int y, t_map *m)
{
	if (x < 0 || y < 0 || x >= m->width || y >= m->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	ft_flood_fill(map, x + 1, y, m);
	ft_flood_fill(map, x - 1, y, m);
	ft_flood_fill(map, x, y + 1, m);
	ft_flood_fill(map, x, y - 1, m);
}

void	ft_flood_fill_check(char **map, int x, int y, t_map *m)
{
	if (x < 0 || y < 0 || x >= m->width || y >= m->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'E')
		return ;
	map[y][x] = 'F';
	ft_flood_fill_check(map, x + 1, y, m);
	ft_flood_fill_check(map, x - 1, y, m);
	ft_flood_fill_check(map, x, y + 1, m);
	ft_flood_fill_check(map, x, y - 1, m);
}

int	ft_check_reachable(t_map *m)
{
	char	**copy;
	int		x;
	int		y;
	int		i;
	int		j;

	copy = ft_copy_grid(m->grid);
	if (!copy)
		return (1);
	x = m->px;
	y = m->py;
	ft_flood_fill(copy, x, y, m);
	i = -1;
	while (copy[++i])
	{
		j = -1;
		while (copy[i][++j])
			if (copy[i][j] == 'C' || copy[i][j] == 'E')
				return (ft_free(copy, j), 1);
	}
	ft_free(copy, m->height);
	return (0);
}

int	ft_check_reachable_collectibles(t_map *m)
{
	char	**copy;
	int		x;
	int		y;
	int		i;
	int		j;

	copy = ft_copy_grid(m->grid);
	if (!copy)
		return (1);
	x = m->px;
	y = m->py;
	ft_flood_fill_check(copy, x, y, m);
	i = -1;
	while (copy[++i])
	{
		j = -1;
		while (copy[i][++j])
			if (copy[i][j] == 'C')
				return (ft_free(copy, j), 1);
	}
	ft_free(copy, m->height);
	return (0);
}

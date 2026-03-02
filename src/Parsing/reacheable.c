/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reacheable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 23:31:18 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/02 00:08:15 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../hdr/so_long.h"

void	ft_flood_fill(char **map, int x, int y, int w, int h)
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	ft_flood_fill(map, x + 1, y, w, h);
	ft_flood_fill(map, x - 1, y, w, h);
	ft_flood_fill(map, x, y + 1, w, h);
	ft_flood_fill(map, x, y - 1, w, h);
}
int 	ft_check_reachable(t_map *m)
{
	char **copy;
	int x;
	int y;
	int i;
	int j;

	copy = ft_copy_grid(m->grid);
	if (!copy)
		return (1);
	x = m->px;
	y = m->py;
	ft_flood_fill(copy, x, y, m->width, m->height);
	i = -1;
	while(copy[++i])
	{
		j = -1;
		while (copy[i][++j])
			if (copy[i][j] == 'C' || copy[i][j] == 'E')
				return (ft_free(copy, j), 1);
	}
	ft_free(copy, m->height);
	return (0);
}

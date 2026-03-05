/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:35:42 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/05 23:00:48 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

char	**ft_append_row(char **grid, int height, char *row)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (height + 2));
	if (!new_grid)
		return (NULL);
	i = -1;
	while (++i < height)
		new_grid[i] = grid[i];
	new_grid[height] = row;
	new_grid[height + 1] = NULL;
	free (grid);
	return (new_grid);
}

int	ft_check_walls(t_map *m)
{
	int	x;
	int	y;

	x = 0;
	while (x < m->width)
		if (m->grid[0][x++] != '1')
			return (1);
	x = 0;
	while (x < m->width)
		if (m->grid[m->height - 1][x++] != '1')
			return (1);
	y = 0;
	while (y < m->height)
	{
		if (m->grid[y][0] != '1' || m->grid[y][m->width - 1] != '1')
			return (1);
		y++;
	}
	return (0);
}

int	ft_valid_and_count_row(t_map *m, char *row, int y)
{
	int	x;

	x = -1;
	while (row[++x])
	{
		if (row[x] != '0' && row[x] != '1' && row[x] != 'C'
			&& row[x] != 'E' && row[x] != 'P')
			return (1);
		if (row[x] == 'C')
			m->c_count++;
		if (row[x] == 'E')
			m->e_count++;
		if (row[x] == 'P')
		{
			m->p_count++;
			m->px = x;
			m->py = y;
		}
	}
	return (0);
}

int	ft_is_ber(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (file[len - 4] == '.' && file[len - 3] == 'b'
		&& file[len - 2] == 'e' && file[len - 1] == 'r')
		return (1);
	return (0);
}

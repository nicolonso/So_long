/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:47:20 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/03 23:03:44 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

// This one I can move it with other initialize structures later

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

int ft_valid_and_count_row(t_map *m, char *row, int y)
{
	int x;

	x = -1;
	while(row[++x])
	{
		if (row[x] != '0' && row[x] != '1' && row[x] != 'C' && row[x] != 'E' && row[x] != 'P')
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

char	**ft_append_row(char **grid, int height, char *row)
{
	char **new_grid;
	int i;

	new_grid = malloc(sizeof(char *) * (height + 2)); // + 1 for new row, +1 for NULL
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

int ft_read_map_gnl(int fd, t_map *m)
{
	char	*line;
	char 	*row;
	int		len;

	ft_init_map(m);
	while ((line = get_next_line(fd)) != NULL)
	{
		len = ft_line_len_no_nl(line);
		if (len == 0)
			return (free(line), 1);
		if (m->width == -1)
			m->width = len;
		else if (len != m->width)
			return (free(line), 1);
		row = ft_dup_no_nl(line);
		free(line);
		if (!row)
			return (1);
		if (ft_valid_and_count_row(m, row, m->height))
			return (free(row), 1);
		m->grid = ft_append_row(m->grid, m->height, row);
		if (!m->grid)
			return (free(row), 1);
		m->height++;
	}
	// after this made a void function 
	if (m->height == 0 || m->width <= 0)
		return (1);
	if (m->c_count < 1 || m->p_count != 1 || m->e_count != 1)
		return (1);
	return (0);
}

int	ft_check_walls(t_map *m)
{
	int x;
	int y;

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

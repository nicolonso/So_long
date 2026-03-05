/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:47:20 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/05 22:51:15 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

static int	ft_fail_line(char *line)
{
	if (line)
		free(line);
	return (1);
}

static int	ft_fail_row(char *row)
{
	if (row)
		free(row);
	return (1);
}

static int	ft_process_line(t_map *m, char *line)
{
	char	*row;
	int		len;

	len = ft_line_len_no_nl(line);
	if (len == 0)
		return (ft_fail_line(line));
	if (m->width == -1)
		m->width = len;
	else if (len != m->width)
		return (ft_fail_line(line));
	row = ft_dup_no_nl(line);
	free(line);
	if (!row)
		return (1);
	if (ft_valid_and_count_row(m, row, m->height))
		return (ft_fail_row(row));
	m->grid = ft_append_row(m->grid, m->height, row);
	if (!m->grid)
		return (ft_fail_row(row));
	m->height++;
	return (0);
}

int	ft_read_map_gnl(int fd, t_map *m)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_process_line(m, line))
			return (1);
	}
	if (m->height == 0 || m->width <= 0)
		return (1);
	if (m->c_count < 1 || m->p_count != 1 || m->e_count != 1)
		return (1);
	return (0);
}

int	ft_parsing(char **av, t_map *m)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	ft_init_map(m);
	if (ft_read_map_gnl(fd, m))
	{
		get_next_line(-1);
		return (ft_free_grid(m->grid),
			write (2, "Error\nInvalid map\n", 18), close(fd), 1);
	}
	close(fd);
	if (ft_check_walls(m))
		return (ft_free_grid(m->grid),
			write (2, "Error\nMap not closed by walls\n", 30), 1);
	else if (ft_check_reachable(m))
		return (ft_free_grid(m->grid),
			write (2, "Error\nMap is not reacheable\n", 29), 1);
	else if (ft_check_reachable_collectibles(m))
		return (ft_free_grid(m->grid),
			write (2, "Error\nMap is not reacheable\n", 29), 1);
	return (0);
}

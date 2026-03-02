/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:58:54 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/01 23:18:43 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"


int	ft_line_len_no_nl(const char *line)
{
	int	i;
	
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

char *ft_dup_no_nl(char *line)
{
	int	len;
	char *row;
	int i;

	len = ft_line_len_no_nl(line);
	row = malloc(len + 1);
	if (!row)
		return (NULL);
	i = -1;
	while (++i < len)
		row[i] = line[i];
	row[i] = '\0';
	return (row);
}

void ft_free(char **ptr, int row)
{
	int i = 0;
	while (i < row)
		free(ptr[i++]);
	free (ptr);
}

int ft_len_map_square(char **map)
{
	int	i;

	i = -1;
	while (map[++i]);
	return (i);
}
//I need modify this one

char **ft_copy_grid(char **map)
{
	char **map_copy;
	int row;
	int col;
	int	len_row;
	int	len_col;

	len_row = ft_len_map_square(map);
	map_copy = (char **) malloc((len_row + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	row = -1;
	while(++row < len_row)
	{
		len_col = ft_line_len_no_nl(map[row]);
		map_copy[row] = (char *) malloc((len_col + 1) * sizeof(char));
		if (!map_copy[row])
			return(ft_free(map_copy, len_row), NULL);
		col = -1;
		while(++col < len_col)
 			map_copy[row][col] = map[row][col];
		map_copy[row][col] = '\0';
	}
	map_copy[row] = NULL; 
	return (map_copy);
}



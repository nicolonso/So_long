/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:07:45 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/18 23:30:51 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../hdr/so_long.h"


/* The base and the structure of So-Long is already done and is working well, the 
first step is set up and envoirment that can compile my program every time that include
my own library, an the minilbx library as is neccessary for this project.

The next stept is make that the program create and windown, as we already ionvestigaty is a vital that
we need to work with .ber files that is the container of my video game and is givin me the structure 
of my program */

//PArsing plan 
/* Data you track while reading

width (set from first line, without \n)

height

counts: p_count, e_count, c_count

char **map (store each row, without \n)

player position (px, py) when you see P


 */



static int line_len_no_nl(const char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return(i);
}

/* void Parsing(char *str)
{
	int i = 0;
	int width = 0;
	int height = 0;
	int Collectible = 0;
	int Player = 0;
	int Exit = 0;
	
	if (ft_strlen(str) == 0)
		return (1);
	while (str[i])
	{
		if (widht_len(str))
			width++;//For this i need to implement the version of the strlen yjthst otavio told me 
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C' && str[i] != 'P' && str[i] != 'E')
			return (1);
		if (str[i] == '\n')
			height++;
		if (str[i] == 'C')
			Collectible++;
		if (str[i] == 'P')
			Player++;
		if(str[i] == 'E') // I need to include if is more than one return 
			Exit++;
	}
} */
int parse_map_str(const char *str)
{
    int i = 0;
    int width;
    int col = 0;
    int height = 0;
    int c_count = 0, p_count = 0, e_count = 0;

    if (!str || str[0] == '\0')
        return 1;

    width = line_len_no_nl(str);
    if (width == 0)
        return 1;

    while (str[i])
    {
        char ch = str[i];

        if (ch == '\n')
        {
            if (col != width)      // not rectangular
                return 1;
            height++;
            col = 0;
        }
        else
        {
            if (ch != '0' && ch != '1' && ch != 'C' && ch != 'P' && ch != 'E')
                return 1;

            if (ch == 'C') c_count++;
            if (ch == 'P') p_count++;
            if (ch == 'E') e_count++;

            col++;
        }
        i++;
    }

    // handle last line if file doesn't end with '\n'
    if (col > 0)
    {
        if (col != width)
            return 1;
        height++;
    }

    // counts rules (basic)
    if (p_count != 1 || e_count != 1 || c_count < 1)
        return 1;

    // you still need wall checks + flood fill later
    return 0;
}
// 3) Helper: duplicate line but remove \n

static char *dup_no_nl(char *line)
{
    int     len;
    char    *row;
    int     i;

    len = line_len_no_nl(line);
    row = malloc(len + 1);
    if (!row)
        return NULL;
    i = 0;
    while (i < len)
    {
        row[i] = line[i];
        i++;
    }
    row[i] = '\0';
    return row;
}
// 4) Validate characters + count C/P/E while reading
static int valid_and_count_row(t_map *m, char *row, int y)
{
    int x = 0;

    while (row[x])
    {
        if (row[x] != '0' && row[x] != '1' && row[x] != 'C'
            && row[x] != 'P' && row[x] != 'E')
            return 1;

        if (row[x] == 'C') m->c_count++;
        if (row[x] == 'E') m->e_count++;
        if (row[x] == 'P')
        {
            m->p_count++;
            m->px = x;
            m->py = y;
        }
        x++;
    }
    return 0;
}


// 5) Read map with GNL and store into grid
static char **append_row(char **grid, int height, char *row)
{
    char **new_grid;
    int   i;

    new_grid = malloc(sizeof(char *) * (height + 2)); // +1 for new row, +1 for NULL
    if (!new_grid)
        return NULL;
    i = 0;
    while (i < height)
    {
        new_grid[i] = grid[i];
        i++;
    }
    new_grid[height] = row;
    new_grid[height + 1] = NULL;
    free(grid);
    return new_grid;
}


// 5. Read with GNL

int read_map_gnl(int fd, t_map *m)
{
    char *line;
    char *row;

    // init
    m->grid = NULL;
    m->width = -1;
    m->height = 0;
    m->c_count = 0;
    m->p_count = 0;
    m->e_count = 0;
    m->px = -1;
    m->py = -1;

    while ((line = get_next_line(fd)) != NULL)
    {
        int len = line_len_no_nl(line);

        // reject empty line (including a blank line at end)
        if (len == 0)
        {
            free(line);
            return 1;
        }

        // set width on first row
        if (m->width == -1)
            m->width = len;
        else if (len != m->width)
        {
            free(line);
            return 1; // not rectangular
        }

        row = dup_no_nl(line);
        free(line);
        if (!row)
            return 1;

        if (valid_and_count_row(m, row, m->height))
        {
            free(row);
            return 1;
        }

        m->grid = append_row(m->grid, m->height, row);
        if (!m->grid)
        {
            free(row);
            return 1;
        }
        m->height++;
    }

    if (m->height == 0 || m->width <= 0)
        return 1;

    // basic counts (walls + flood fill later)
    if (m->p_count != 1 || m->e_count != 1 || m->c_count < 1)
        return 1;

    return 0;
}

// 6) Next check: walls (after read)
int check_walls(t_map *m)
{
    int x, y;

    // top row
    x = 0;
    while (x < m->width)
        if (m->grid[0][x++] != '1') return 1;

    // bottom row
    x = 0;
    while (x < m->width)
        if (m->grid[m->height - 1][x++] != '1') return 1;

    // left/right walls
    y = 0;
    while (y < m->height)
    {
        if (m->grid[y][0] != '1' || m->grid[y][m->width - 1] != '1')
            return 1;
        y++;
    }
    return 0;
}


int main(int ac, char **av)
{
    int   fd;
    t_map m;

    if (ac != 2)
        return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 34), 1);

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);

    if (read_map_gnl(fd, &m))
        return (write(2, "Error\nInvalid map\n", 18), close(fd), 1);

    close(fd);

    if (check_walls(&m))
        return (write(2, "Error\nMap not closed by walls\n", 30), 1);
	
    // next: flood fill validation

    return 0;
}






































/* int main(int ac, char **av)
{
	int		fd;
	//char	*map;
	char	*line;
	
	if (ac != 2)
	{
		write(2,"Error\nUsage: ./so_long <map.ber>\n", 34);
		exit (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	// lseek(fd, 0, SEEK_SET); Search for this function and what it does
	if (fd == -1)
	{
        ft_printf("Error\nCould not open file: %s\n", av[1]);
		perror("open");
        return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("%s", line);
		free (line);
	}
	close (fd);
	return (0);	
} */


